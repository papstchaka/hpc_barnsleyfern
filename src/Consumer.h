#ifndef CONSUMER_H
// imports
#include "Buffer.h" // for buffer
#include "Worker.h" // for inheritance

#include <iostream>

/*!class that implements the basic consumer in the producer - consumer model*/
template <typename T>
class Consumer : public Worker
{
public:
    /**
     * constructor of Consumer class
     * @param buffer: buffer to use [Buffer]
     * @param numThreads: number of threads that are used [unsigned int]
     * @def Worker [Worker]
     * @def m_buffer [Buffer]
     * @def numberOfThreads [unsigned int]
     */
    explicit Consumer(Buffer<T>& buffer, unsigned int& numThreads) : Worker(), m_buffer(buffer), numberOfThreads(numThreads) {};
    /**
     * 'worker' function that does the actual work
     * @return true: when finished, returns true to stop the worker [Boolean]
     */
    bool step() override
    {
        // init item to pop
        T item;
        // as long as not finished
        while (!finished)
        {
            // we have to catch the runtime error from the buffer in here!
            try
            {
                // get last item from buffer
                m_buffer.popItem(item);
                // 'consume' the item via RealConsumer
                finished = consume(&item);
            }
            // catch runtime error
            catch (const std::runtime_error& error)
            {
                // Consumer has done his work
                finished = true;
            }
        }
        // lock mutex to save the counter of finished threads
        std::lock_guard<std::mutex> guard(mutexThreadCount);
        // increment number of finished threads
        finishedThreads += 1;
        std::cout << finishedThreads << std::endl;
        // if all threads are finished
        if (finishedThreads == numberOfThreads)
        {
            // finish the work
            finishWork();
        }
        return true;
    }

private:
    bool finished = false; // whether Consumer has done his work or not
    Buffer<T>& m_buffer; // actual buffer
    static unsigned int finishedThreads; // number of finished threads
    static std::mutex mutexThreadCount; // mutex to save the counter of finished threads
    unsigned int numberOfThreads; // number of threads that work on the task

protected:
    /**
     * function that finishes the work if all Consumers have done their task
     */
    virtual void finishWork() {};
    /**
     * 'consume' function that does the actual work
     * @param t: item to use for the work [T]
     * @return finished: whether task is finished or not [Boolean]
     */
    virtual bool consume(T* t) { return 0; };
};

template <class T>
unsigned int Consumer<T>::finishedThreads = 0; // init number of finished threads to be 0
template <class T>
std::mutex Consumer<T>::mutexThreadCount; // init mutex to save the counter

#endif // !CONSUMER_H