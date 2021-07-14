#pragma once

#include "stop.h"
#include "bus.h"
#include "string_view"
#include "optional"
#include "unordered_map"
#include "unordered_set"
#include "iostream"

std::pair<std::string_view, std::optional<std::string_view>>
SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");

std::string_view ReadToken(std::string_view &s, std::string_view delimiter = " ");

void trimStart(std::string_view &line);

void trimEnd(std::string_view &line);

std::pair<bool, std::vector<std::string_view>> split(std::string_view line);

int ConvertToInt(std::string_view str);

class StationManager {
private:
    std::unordered_map<std::string, BusStop> busStops;
    std::unordered_map<std::string, Bus> buses;
public:
    void readBusStop(std::string_view line);

    void readBus(std::string_view line);

    std::string showInfoForBus(const std::string& number) const;

    double calculateRouteLength(const std::string& number) const;
};
