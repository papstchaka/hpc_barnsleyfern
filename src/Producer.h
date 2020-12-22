#ifndef PRODUCER_H
// imports
#include "Buffer.h" // for buffer
#include "Worker.h" // for worker

/*!class that implements the basic producer in the producer - consumer model*/
template <typename T>
class Producer : public Worker
{
public:
    /**
     * constructor of Producer
     * @param buffer: given buffer [Buffer]
     * @set Worker [Worker]
     * @set m_buffer [Buffer]
     */
    explicit Producer(Buffer<T>& buffer) : Worker(), m_buffer(buffer) {};
    /**
     * 'worker' function that does the actual work
     * @return true: when finished, returns true to stop the worker [Boolean]
     */
    bool step() override
    {
        // init new item
        T item;
        // as long as not finished
        while (!finished)
        {
            // 'produce' the item via RealProducer
            finished = produce(&item);
            // push item to buffer
            m_buffer.pushItem(item);
        }
        return true;
    }

private:
    bool finished = false; // whether Producer has done his work or not
    Buffer<T>& m_buffer; // actual buffer

protected:
    /**
     * 'produce' function that does the actual work
     * @param t: item to use for the work [T]
     * @return finished: whether task is finished or not [Boolean]
     */
    virtual bool produce(T*) { return 0; };
};

#endif // !PRODUCER_H