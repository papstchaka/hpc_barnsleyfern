// imports
#include "Point.h" // for Points


std::discrete_distribution<int> Point::m_distribution = std::discrete_distribution<int>({0.01, 0.85, 0.07, 0.07}); //init given distribution
std::random_device Point::m_random_device; // init randomizer

/**
 * determine next point
 * @param point: current point [Point]
 * @return new_point: next point [Point]
 */
std::pair<float,float> Point::getNextPoint(std::pair<float,float> point)
 {
     // get a new random value, of one of the four sets
     unsigned int set = m_distribution(m_random_device);
     // set current temporary x and y
     float temp_x = point.first, temp_y = point.second;
     // get corresponding values according to the given set
     if(set == 0)
     {
         point.first = 0.0f;
         point.second = 0.16f*temp_y;
     }
     if(set == 1)
     {
         point.first = 0.85f*temp_x + 0.04f*temp_y;
         point.second = -0.04f*temp_x + 0.85f*temp_y + 1.6f;
     }
     if(set == 2)
     {
         point.first = 0.2f*temp_x - 0.26f*temp_y;
         point.second = 0.23f*temp_x + 0.22f*temp_y + 1.6f;
     }
     if(set == 3)
     {
         point.first = -0.15f*temp_x + 0.28f*temp_y;
         point.second = 0.26f*temp_x + 0.24f*temp_y + 0.44f;
     }
     return point;
 }