// imports
#include <random> // for random values

/*!class that implements Point objects*/
class Point
{
public:
    /**
     * constructor of Point
     * @set m_point
     */
    Point() : m_point(std::make_pair(0,0)) {};
    /**
     * determine next point
     * @param point: current point [Point]
     * @return new_point: next point [Point]
     */
    static std::pair<float,float> getNextPoint(std::pair<float,float> point);
    std::pair<float,float> m_point; // point itself
    
private:
    static std::discrete_distribution<int> m_distribution; // init the distribution with given probabilities
    static std::random_device m_random_device; // init the randomizer
};
