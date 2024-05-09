
#ifndef YARAOSUD_HAVERSINE_H
#define YARAOSUD_HAVERSINE_H
#include "Include.h"
class Haversine {
    using angle_t = double;
    using radians_t = double;
    using kilometers_t = double;
public:
    static auto calculate_distance(const angle_t latitude1, const angle_t longitude1, const angle_t latitude2, const angle_t longitude2) -> kilometers_t;
    static auto convert(const angle_t angle) -> radians_t;

};
#endif //YARAOSUD_HAVERSINE_H