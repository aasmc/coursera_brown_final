#include "bus.h"
#include "algorithm"
#include "set"

Bus::Bus(std::vector<std::string> stops_, bool isCircular_) :
        forward_stops(std::move(stops_)), isCircular(isCircular_) {}


int Bus::getNumberOfStopsOnRoute() const {
    return forward_stops.size();
}

int Bus::getUniqueStops() const {
    std::set<std::string> unique = {forward_stops.begin(), forward_stops.end()};
    return unique.size();
}

void Bus::addBusStop(const std::string &stop_name) {
    forward_stops.push_back(stop_name);
}

void Bus::setCircular(bool isCircular_) {
    isCircular = isCircular_;
}

void Bus::setNumber(const std::string &number_) {
    number = number_;
}

std::string Bus::getNumber() const {
    return number;
}

size_t Bus::getTotalNumberOfStops() const {
    return forward_stops.size();
}

const std::vector<std::string> &Bus::getBusStops() const {
    return forward_stops;
}

bool Bus::isBusCircular() const {
    return isCircular;
}


















