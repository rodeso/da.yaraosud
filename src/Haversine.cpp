#include "../include/Haversine.h"

auto Haversine::calculate_distance(const Haversine::angle_t latitude1, const Haversine::angle_t longitude1,
                                   const Haversine::angle_t latitude2,
                                   const Haversine::angle_t longitude2) -> kilometers_t {
    const auto earths_radius = kilometers_t{6371};

    // Get the difference between our two points then convert the difference into radians
    const auto lat_delta = convert(latitude2 - latitude1);
    const auto lon_delta = convert(longitude2 - longitude1);

    const auto converted_lat1 = convert(latitude1);
    const auto converted_lat2 = convert(latitude2);

    const auto a = pow(sin(lat_delta / 2), 2) + cos(converted_lat1) * cos(converted_lat2) * pow(sin(lon_delta / 2), 2);
    const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
    const auto d = earths_radius * c;

    return d;
}

// convert our passed value to radians_t
auto Haversine::convert(const angle_t angle) -> radians_t {
    return angle * (3.14159265358979323846 / 180);
}