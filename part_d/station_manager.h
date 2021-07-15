#pragma once

#include "stop.h"
#include "bus.h"
#include "string_view"
#include "optional"
#include "unordered_map"
#include "unordered_set"
#include "iostream"


class StationManager {
private:
    std::unordered_map<std::string, BusStop> busStops;
    std::unordered_map<std::string, Bus> buses;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> distances;
public:

    void addDistanceFor(const std::string& from, const std::string &to, int distance);

    void addBus(const Bus &bus);

    void addBusStop(const BusStop &busStop);

    std::string showInfoForBus(const std::string &number, int request_id) const;

    std::string showInfoForStop(const std::string &stop, int request_id) const;

    double calculateGeographicRouteLength(const std::string &number) const;

    int calculateRouteLength(const std::string &number) const;
};
