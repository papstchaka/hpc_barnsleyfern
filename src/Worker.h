#ifndef WORKER_H
// imports
#include <thread> // for threading
#pragma once // make sure source file gets only included once
/*!class that implements the Worker*/
class Worker
{
public:
    /**
     * constructor of Worker. Default - does nothing
     */
    Worker() = default;
    /**
     * inits and starts the thread
     */
    void start();
    /**
     * stops the thread, deconstructs it
     */
    void stop();
    /**
     * joining function. joins the thread, stops it afterwards
     */
    void join();

private:
    std::thread m_thread; // thread object
    bool m_terminate = false; // init bool whether thread is terminated to false
    bool m_running = false; // init bool whether thread is running to false
    /**
     * working function
     */
    void work();
    /**
     * checks whether thread is running
     * @return m_running: whether thread is running or not [Boolean]
     */
    bool isRunning() const;
    /**
     * checks whether thread is already terminated
     * @return m_terminate: whether thread is terminated or not [Boolean]
     */
    bool isTerminated() const;

protected:
    /**
     * 'worker' function that does the actual work
     * @return true: when finished, returns true to stop the worker [Boolean]
     */
    virtual bool step() { return false; };
};

#endif // !WORKER_H