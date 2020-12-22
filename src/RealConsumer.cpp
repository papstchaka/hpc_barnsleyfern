// imports
#include "RealConsumer.h" // the header
#include <cmath> // to round the values to integers

// constants for window size
#define INIT_X -2.2 // initial x
#define INIT_Y 0.0 // initial y
#define FINAL_X 2.7 // final x
#define FINAL_Y 10.0 // final y
// make rendering
#define m_slope_x (WINDOW_X/(FINAL_X - INIT_X)) // scale factor x
#define m_slope_y (WINDOW_Y/(FINAL_Y - INIT_Y)) // scale factor y
#define m_intercept_x (-(m_slope_x*INIT_X)) // bias x
#define m_intercept_y (-(m_slope_y*INIT_Y)) // bias y

/**
 * constructor of RealConsumer. Creates the image of not done yet
 * @param buffer: buffer to use [Buffer]
 * @param numThreads: numThreads: number of threads that are used [unsigned int]
 * @set Consumer [Consumer]
 */
RealConsumer::RealConsumer(Buffer<std::pair<float, float>> &buffer, unsigned int& numThreads) : Consumer<std::pair<float, float>>(buffer, numThreads)
{
    createImage();
}

cimg_library::CImg<unsigned char> RealConsumer::m_image = cimg_library::CImg<unsigned char>(WINDOW_X, WINDOW_Y, 1, 1); // init image with desired size
bool RealConsumer::isImageCreated = false; // init Bool whether image is already created to false
std::mutex RealConsumer::mutexSingleConsument; // init mutex to save a single consument
std::mutex RealConsumer::pictureMutexes[WINDOW_Y]; // init the mutexes for the image

/**
 * 'consume' function that does the actual work
 * @param point: point to use for the work [std::pair<float,float>]
 * @return finished: whether task is finished or not [Boolean]
 */
bool RealConsumer::consume(std::pair<float, float>* point)
{
    // convert the point to a pixel value
    std::pair<int,int> pixel = RealConsumer::convert2Pixel(*point);
    // get x and y value from pixel
    int x = pixel.first, y = pixel.second;
    // lock mutex to save image
    std::lock_guard<std::mutex> guard(pictureMutexes[y]);
    // get current pixel value of given pixel
    unsigned char *colorValue = m_image.data(x, y, 0, 0);
    // check whether current pixel value is below 255 -> prevent overflow
    // nothing hsa to be done if value is already set to 255
    if (*colorValue <= 255)
    {
        //increment pixel value and set new value to current pixel
        *colorValue += 1;
        m_image.draw_point(x, y, colorValue);
    }
    return false;
}

/**
 * function that finishes the work if all Consumers have done their task. Saves the image
 */
void RealConsumer::finishWork()
{
    m_image.save_png("barnsley_fern.png");
}

/**
 * function that creates the image and inits all pixel values to 0 = black
 */
void RealConsumer::createImage()
{
    // make sure that image wasn't already created
    if (!isImageCreated) {
        // lock to prevent from multiple creations
        std::lock_guard<std::mutex> guard(mutexSingleConsument);
        // fill with black
        m_image.fill(0);
        // "image is now created"
        isImageCreated = true;
    }
}

/**
 * converts given point (from producer) into pixel values (for the image)
 * @param point: point given by producers [std::pair<float,float>]
 * @return pixel: pixel value [std::pair<int,int>]
 */
std::pair<int,int> RealConsumer::convert2Pixel(std::pair<float,float> point)
{
    // scale x value and add bias, make int from float
    int x = floor(point.first*m_slope_x + m_intercept_x);
    // scale y value and add bias, make int from float
    int y = floor(point.second*m_slope_y + m_intercept_y);
    return std::make_pair(x,y);
}
