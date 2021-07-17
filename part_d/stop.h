//#pragma once
//
//#include "cmath"
//#include "string"
//#include "set"
//#include "unordered_map"
//
//class BusStop {
//private:
//    static constexpr double PI = 3.1415926535;
//    static constexpr int EARTH_RADIUS = 6371000;
//    std::string name;
//    double latitude;
//    double longitude;
//    std::set<std::string> busNumbers;
//    std::unordered_map<std::string, int> distances;
//
//    double toRadians(double degree) const;
//
//public:
//    BusStop();
//
//    BusStop(std::string name_, double lat, double lon);
//
//    double computeGeographicDistance(const BusStop &other) const;
//
//    double getLongitude() const;
//
//    double getLatitude() const;
//
//    void setName(const std::string &name_);
//
//    void setLatitude(const double &latitude_);
//
//    void setLongitude(const double  &longitude_);
//
//    std::string getName() const;
//
//    void addBus(const std::string &busNumber_);
//
//    const std::set<std::string>& getBusNumbers() const;
//
//    const std::unordered_map<std::string, int>& getDistances() const;
//
//    void setDistances(const std::unordered_map<std::string, int> &distances_);
//};
