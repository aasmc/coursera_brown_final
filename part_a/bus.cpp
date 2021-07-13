#include "bus.h"

Bus::Bus(std::vector<std::string> stops_, bool isCircular_) :
        stops(std::move(stops_)), isCircular(isCircular_) {}


int Bus::getNumberOfStopsOnRoute() const {
    if (isCircular) {
        return stops.size();
    } else {
        return stops.size() * 2 - 1;
    }
}

int Bus::getUniqueStops() const {
    if (isCircular) {
        return stops.size() - 1;
    } else {
        return stops.size();
    }
}

void Bus::addBusStop(const std::string &stop_name) {
    stops.push_back(stop_name);
}

void Bus::setCircular(bool isCircular_) {
    isCircular = isCircular_;
}

void Bus::setNumber(int number_) {
    number = number_;
}

int Bus::getNumber() const {
    return number;
}

size_t Bus::getTotalNumberOfStops() const {
    return stops.size();
}

const std::vector<std::string>& Bus::getBusStops() const {
    return stops;
}

bool Bus::isBusCircular() const {
    return isCircular;
}


















