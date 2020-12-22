#ifndef REALPRODUCER_H
// imports
#include "Producer.h" // for producers
#include "Point.h" // for the point conversion
/*!class that implements the RealProducer*/
class RealProducer : public Producer<std::pair<float, float>>
{
public:
    /**
     * constructor of RealProducer
     * @param buffer: buffer to use [Buffer]
     * @set Producer [Producer]
     */
    explicit RealProducer(Buffer<std::pair<float, float>>& buffer) : Producer<std::pair<float, float>>(buffer) {};
    /**
     * 'produce' function that does the actual work
     * @param new_point: point to produce [std::pair<float,float>]
     * @return finished: whether task is finished or not [Boolean]
     */
    bool produce(std::pair<float, float>* new_point) override
    {
        // determine the next point
        m_point.m_point = m_point.getNextPoint(m_point.m_point);
        // return reference to next point
        *new_point = m_point.m_point;
        // check whether enough points were already produced. If yes, break up, otherwise continue
        if (i < m_numbers - 1) { i++; return false;}
        else { return true; }
    }

private:
    Point m_point; // point object
    unsigned int i = 0; // counter for number of produced points by current producer
    const unsigned int m_numbers = 1e8; // max number of points to produce per producer = 10^8
};

#endif // !REALPRODUCER_H
