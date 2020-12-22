// imports
#include "Worker.h" // for workers

/**
 * joining function. joins the thread, stops it afterwards
 */
void Worker::join()
{
    // join the thread -> waiting for it to finish
    m_thread.join();
    // stop it afterwards
    stop();
}

/**
 * inits and starts the thread
 */
void Worker::start()
{
    // check if thread already running
    if (!isRunning())
    {
        // start otherwise
        m_thread = std::thread([this] () { work(); });
        // set booleans correspondingly
        m_running = true;
        m_terminate = false;
    }
}

/**
 * stops the thread, deconstructs it
 */
void Worker::stop()
{
    // check if thread already terminated
    if (isTerminated())
    {
        // set booleans correspondingly
        m_terminate = true;
        m_running = false;
        // deconstruct thread
        m_thread.~thread();
    }
}

/**
 * working function
 */
void Worker::work()
{
    // as long as thread not finished yet - gets decided by child classes
    while (!isTerminated())
    {
        // do the work
        m_terminate = step();
    }
    // set termination bool to true
    m_terminate = true;
}

/**
 * checks whether thread is running
 * @return m_running: whether thread is running or not [Boolean]
 */
bool Worker::isRunning() const
{
    return m_running;
}

/**
 * checks whether thread is already terminated
 * @return m_terminate: whether thread is terminated or not [Boolean]
 */
bool Worker::isTerminated() const
{
    return m_terminate;
}