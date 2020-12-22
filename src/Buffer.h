#ifndef BUFFER_H
// imports
#include <cstddef> // for size_t variables
#include <memory> // for unique_ptr variables
#include <mutex> // for mutex variables
#include <condition_variable> // for condition variables
#pragma once // make sure source file gets only included once

/*!class that implements the ring buffer for consumers and producers*/
template <typename T>
class Buffer
{
public:
    /**
     * constructor of Buffer class
     * @param size: desired size of buffer
     * @def m_buffer [unique_ptr<T>]
     * @def m_size [size_t]
     */
    explicit Buffer(std::size_t& size) : m_buffer(std::unique_ptr<T[]>(new T[size])), m_size(size) {};
    /**
     * pushing items into the buffer
     * @param item: reference to item to push [T]
     */
    void pushItem(T &item)
    {
        // lock the mutex
        std::unique_lock<std::mutex> lock(m_mutex);
        // wait for condition variable to be sure that there is still capacity in the buffer
        hasCapacity.wait(lock, [this, &item] {
            if (this->isFull()) return false; else return true;
        });
        // place item on the current position of the head
        m_buffer[m_head] = item;
        if (this->isFull())
        {
            // set the tail new if buffer is full
            m_tail = (m_tail + 1) % m_size;
        }
        // increment head
        m_head = (m_head + 1) % m_size;
        // check if buffer now full
        m_full = m_head == m_tail;
        // notify one of the threads that new data is available
        hasData.notify_one();
    }
    /**
     * getting the last item (being the first that was pushed in) from the buffer
     * @param item: reference to item to pop [T]
     */
    void popItem(T &item)
    {
        // lock the mutex
        std::unique_lock<std::mutex> lock(m_mutex);
        // set the timeout to be current time + desired time
        auto timeout = std::chrono::system_clock::now() + m_timeout;
        // wait for condition variable. Either wait until new data is available in the buffer or the timeout is reached
        if (hasData.wait_until(lock, timeout, [this] {if (this->isEmtpy()) return false; else return true;}))
        {
            ; // if timeout is not reached
        }
        else
        {
            // if timeout is reached, throw runtime error
            throw std::runtime_error("Buffer empty!!!");
        }
        // read data and advance the tail (we now have a free space)
        item = m_buffer[m_tail];
        // buffer is not full (anymore)
        m_full = false;
        // increment tail
        m_tail = (m_tail + 1) % m_size;
        // notify one of the threads that capacity has increased
        hasCapacity.notify_one();
    }
    /**
     * resets the buffer (to be empty)
     */
    void resetBuffer()
    {
        // lock the mutex
        std::lock_guard<std::mutex> lock(m_mutex);
        // set head to be same as tail
        m_head = m_tail;
        // buffer is now empty
        m_full = false;
    }
    /**
     * check whether buffer is empty
     * @return m_empty: whether buffer is full or not [Boolean]
     */
    bool isEmtpy() const
    {
        // if head and tail are equal, we are empty
        return (!m_full && (m_head == m_tail));
    }
    /**
     * check whether buffer is emtpy
     * @return m_full: whether buffer is full or not [Boolean]
     */
    bool isFull() const
    {
        // if tail is ahead the head by 1, we are full
        return m_full;
    }
    /**
     * gets Capacity of buffer
     * @return m_size: capacity of buffer [size_t]
     */
    std::size_t getCapacity() const
    {
        return m_size;
    }
    /**
     * counts the amount of elements in the buffer
     * @return numElements: number of elements in buffer [size_t]
     */
    std::size_t getElementCount() const
    {
        // init number of elements to be all that fit into the buffer
        std::size_t numElements = m_size;
        // if buffer is not full
        if (!this->isFull())
        {
            // check whether head is before tails, then just subtract tail from head
            if (m_head >= m_tail)
            {
                numElements = m_head - m_tail;
            }
            // else, subtract tail from sum of head and size
            else
            {
                numElements = m_size + m_head - m_tail;
            }
        }
        return numElements;
    }

private:
    std::mutex m_mutex; // mutex to save the buffer
    std::unique_ptr<T[]> m_buffer; // buffer object itself
    std::size_t m_head = 0; // head of buffer
    std::size_t m_tail = 0; // tail of buffer
    const std::size_t m_size; // size of buffer
    bool m_full = false; // whether buffer is full or not
    const std::chrono::milliseconds m_timeout = std::chrono::milliseconds(1500); // desired timeout to throw runtime error
    std::condition_variable hasCapacity; // CV for pushing items
    std::condition_variable hasData; // CV for popping items
};

#endif // !BUFFER_H