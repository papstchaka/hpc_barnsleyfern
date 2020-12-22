#ifndef REALCONSUMER_H
// imports
#include "Consumer.h" // for consumers
#define cimg_display 0 // needed for whatever the fuck reason
#include "CImg.h" // for the image

// constants for window size
#define WINDOW_X 10000 // x number of pixels
#define WINDOW_Y 20000 // y number of pixels

/*!class that implements the RealConsumer*/
class RealConsumer : public Consumer<std::pair<float, float>>
{
public:
    /**
     * constructor of RealConsumer. Creates the image of not done yet
     * @param buffer: buffer to use [Buffer]
     * @param numThreads: numThreads: number of threads that are used [unsigned int]
     * @set Consumer [Consumer]
     */
    explicit RealConsumer(Buffer<std::pair<float, float>>& buffer, unsigned int& numThreads);
    /**
     * 'consume' function that does the actual work
     * @param point: point to use for the work [std::pair<float,float>]
     * @return finished: whether task is finished or not [Boolean]
     */
    bool consume(std::pair<float, float>* point) override;

private:
    static cimg_library::CImg<unsigned char> m_image; // the image object
    /**
     * function that creates the image and inits all pixel values to 0 = black
     */
    static void createImage();
    /**
     * function that finishes the work if all Consumers have done their task. Saves the image
     */
    void finishWork() override;
    /**
     * converts given point (from producer) into pixel values (for the image)
     * @param point: point given by producers [std::pair<float,float>]
     * @return pixel: pixel value [std::pair<int,int>]
     */
    static std::pair<int,int> convert2Pixel(std::pair<float,float> point);
    static bool isImageCreated; // whether image was already created or not
    static std::mutex mutexSingleConsument; // mutex to save a single consument
    static std::mutex pictureMutexes[WINDOW_Y]; // init the mutexes for the image
};

#endif // !REALCONSUMER_H