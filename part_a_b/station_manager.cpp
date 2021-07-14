#include "station_manager.h"
#include "sstream"
#include "stdexcept"
#include "iomanip"

double StationManager::calculateRouteLength(const std::string &number) const {
    if (buses.count(number) == 0) {
        throw std::invalid_argument("No such bus: " + number);
    }
    const Bus &bus = buses.at(number);
    if (bus.getTotalNumberOfStops() < 2) {
        return 0;
    }
    const auto &stops = bus.getBusStops();
    double result = 0;
    for (int i = 0; i < stops.size() - 1; ++i) {
        result += busStops.at(stops[i]).computeDistance(busStops.at(stops[i + 1]));
    }
    if (!bus.isBusCircular()) {
        result *= 2;
    }
    return result;
}

std::string StationManager::showInfoForBus(const std::string &number) const {
    std::ostringstream output;
    if (buses.count(number) == 0) {
        output << "Bus " << number << ": not found" << std::endl;
        return output.str();
    }
    const Bus &bus = buses.at(number);
    output << "Bus " << bus.getNumber() << ": " << bus.getNumberOfStopsOnRoute()
           << " stops on route, " << bus.getUniqueStops() << " unique stops, " <<
           std::setprecision(6) <<
           calculateRouteLength(number) << " route length";
    return output.str();
}

void StationManager::addBusStop(const BusStop &busStop) {
    busStops[busStop.getName()] = busStop;
}

void StationManager::addBus(const Bus &bus) {
    buses[bus.getNumber()] = bus;
}





























