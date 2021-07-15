//#pragma once
//
//#include "vector"
//#include "stop.h"
//
//class Bus {
//private:
//    std::string number;
//    bool isCircular = false;
//    std::vector<std::string> stops;
//public:
//
//    Bus() = default;
//
//    void addBusStop(const std::string &stop);
//
//    void setCircular(bool isCircular_);
//
//    void setNumber(const std::string &number_);
//
//    Bus(std::vector<std::string> stops_, bool isCircular_);
//
//    int getNumberOfStopsOnRoute() const;
//
//    int getUniqueStops() const;
//
//    std::string getNumber() const;
//
//    size_t getTotalNumberOfStops() const;
//
//    const std::vector<std::string>& getBusStops() const;
//
//    bool isBusCircular() const;
//
//};