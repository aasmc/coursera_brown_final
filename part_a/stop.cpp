#include "stop.h"

BusStop::BusStop(std::string name_, double lat, double lon)
        : name(std::move(name_)), latitude(lat), longitude(lon) {}

BusStop::BusStop(): name(""), latitude(0.0), longitude(0.0) {}

double BusStop::getLatitude() const {
    return latitude;
}

double BusStop::getLongitude() const {
    return longitude;
}

double BusStop::toRadians(double degree) const {
    return degree * PI / 180;
}

double BusStop::computeDistance(const BusStop &other) const {
    double rLat = toRadians(latitude);
    double rLong = toRadians(longitude);
    double orLat = toRadians(other.latitude);
    double orLong = toRadians(other.longitude);
    return std::acos(std::sin(rLat) * std::sin(orLat) +
                     std::cos(rLat) * std::cos(orLat) *
                     std::cos(std::abs(rLong - orLong))) *
           EARTH_RADIUS;
}
