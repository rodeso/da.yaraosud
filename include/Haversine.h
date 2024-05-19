
#ifndef YARAOSUD_HAVERSINE_H
#define YARAOSUD_HAVERSINE_H
#include "Include.h"

/**
 * @brief Class that represents the system that calculates distances between Nodes.
 */

class Haversine {
    using angle_t = double;
    using radians_t = double;
    using kilometers_t = double;
public:
    /**
    * @brief Calculates the distance between two points on the Earth's surface using the Haversine formula.
    *
    * This function takes the latitude and longitude of two points and calculates the distance between them
    * using the Haversine formula. The result is returned in kilometers.
    *
    * @param latitude1 The latitude of the first point.
    * @param longitude1 The longitude of the first point.
    * @param latitude2 The latitude of the second point.
    * @param longitude2 The longitude of the second point.
    * @return The distance between the two points in kilometers.
    */
    static auto calculate_distance(const angle_t latitude1, const angle_t longitude1, const angle_t latitude2, const angle_t longitude2) -> kilometers_t;

    /**
    * @brief Converts an angle from degrees to radians.
    *
    * This function takes an angle in degrees and converts it to radians.
    *
    * @param angle The angle in degrees.
    * @return The angle converted to radians.
    */
    static auto convert(const angle_t angle) -> radians_t;

};
#endif //YARAOSUD_HAVERSINE_H
