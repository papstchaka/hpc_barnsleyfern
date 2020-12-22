// imports
#include <iostream> // to be able to write on the screen
#include "RealProducer.h" // for the RealProducers
#include "RealConsumer.h" // for the RealConsumers

/**
 * main function of the project
 */
int main()
{
    // set number of Producers
    unsigned int num_prod_threads = 2;
    // set number of Consumers
    unsigned int num_cons_threads = 2;
    // set size of buffer
    std::size_t size = 2e5;
    // init the buffer
    Buffer<std::pair<float,float>> buffer(size);
    // init the producers
    std::vector<RealProducer> producers;
    for (int i=0; i<num_prod_threads; i++)
    {
        // add producer to list of producers
        producers.emplace_back(buffer);
    }
    // init the consumers
    std::vector<RealConsumer> consumers;
    for (int i = 0; i < num_cons_threads; ++i)
    {
        // add consumer to list of consumers
        consumers.emplace_back(buffer, num_cons_threads);
    }
    // start all producers and consumers
    for (auto& t : producers) t.start();
    for (auto& t : consumers) t.start();
    // join on producers and consumers
    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();
    // write that everythin worked
    std::cout << "done with the work" << std::endl;
}