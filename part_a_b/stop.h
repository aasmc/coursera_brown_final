#pragma once

#include "cmath"
#include "string"

class BusStop {
private:
    static constexpr double PI = 3.1415926535;
    static constexpr int EARTH_RADIUS = 6371000;
    std::string name;
    double latitude;
    double longitude;

    double toRadians(double degree) const;

public:
    BusStop();

    BusStop(std::string name_, double lat, double lon);

    double computeDistance(const BusStop &other) const;

    double getLongitude() const;

    double getLatitude() const;

    void setName(const std::string &name_);

    void setLatitude(const double &latitude_);

    void setLongitude(const double  &longitude_);

    std::string getName() const;
};
