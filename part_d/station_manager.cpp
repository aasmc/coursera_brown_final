#include "station_manager.h"
#include "sstream"
#include "stdexcept"
#include "iomanip"

double StationManager::calculateGeographicRouteLength(const std::string &number) const {
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
        result += busStops.at(stops[i]).computeGeographicDistance(busStops.at(stops[i + 1]));
    }
    if (!bus.isBusCircular()) {
        result *= 2;
    }
    return result;
}

std::string StationManager::showInfoForBus(const std::string &number, int request_id) const {
    std::ostringstream output;
    if (buses.count(number) == 0) {
        output << "{ \"request_id\":" << request_id << ","
               << "\"error_message\":" << "\"not found\"" << "}";

        return output.str();
    }
    const Bus &bus = buses.at(number);
    const int routeLength = calculateRouteLength(number);
    const double curvature = routeLength * 1.0 / calculateGeographicRouteLength(number);
    output << std::setprecision(6);
    output << "{" << "\"route_length\":" << routeLength << "," <<
           "\"request_id\":" << request_id << "," <<
           "\"curvature\":" << curvature << "," <<
           "\"stop_count\":" << bus.getNumberOfStopsOnRoute() << "," <<
           "\"unique_stop_count\":" << bus.getUniqueStops() << "}";

    return output.str();
}

void StationManager::addBusStop(const BusStop &busStop) {
    auto &stop = busStops[busStop.getName()];
    stop.setName(busStop.getName());
    stop.setLatitude(busStop.getLatitude());
    stop.setLongitude(busStop.getLongitude());
    stop.setDistances(busStop.getDistances());
}

void StationManager::addBus(const Bus &bus) {
    buses[bus.getNumber()] = bus;
    const auto &stops = bus.getBusStops();
    for (const auto &stop : stops) {
        busStops[stop].addBus(bus.getNumber());
    }
}

std::string StationManager::showInfoForStop(const std::string &stop, int request_id) const {
    std::ostringstream output;
    if (busStops.count(stop) == 0) {
        output << "{ \"request_id\":" << request_id << ","
               << "\"error_message\":" << "\"not found\"" << "}";
    } else if (busStops.at(stop).getBusNumbers().empty()) {
        output << "{ \"buses\": [],"
               << "\"request_id\":" << request_id << "}";
    } else {
        const auto &busNumbers = busStops.at(stop).getBusNumbers();
        output << "{ \"buses\": [";
        bool first = true;
        for (const auto &busNumber : busNumbers) {
            if (!first) {
                output << ',' << "\"" << busNumber << "\"";
            } else {
                output << "\"" << busNumber << "\"";
                first = false;
            }
        }
        output << "],"
               << "\"request_id\":" << request_id << "}";

    }
    return output.str();
}

void StationManager::addDistanceFor(const std::string &from, const std::string &to, int distance) {
    distances[from][to] = distance;
}

int StationManager::calculateRouteLength(const std::string &number) const {
    if (buses.count(number) == 0) {
        throw std::invalid_argument("No such bus: " + number);
    }
    const Bus &bus = buses.at(number);
    if (bus.getTotalNumberOfStops() < 2) {
        return 0;
    }
    const auto &stops = bus.getBusStops();
    int result = 0;
    for (int i = 0; i < stops.size() - 1; ++i) {
        const auto &from = busStops.at(stops[i]);
        const auto &to = busStops.at(stops[i + 1]);
        if (from.getDistances().count(to.getName()) != 0) {
            result += from.getDistances().at(to.getName());
        } else {
            result += to.getDistances().at(from.getName());
        }
    }
    if (!bus.isBusCircular()) {
        for (int i = stops.size() - 1; i > 0; --i) {
            const auto &from = busStops.at(stops[i]);
            const auto &to = busStops.at(stops[i - 1]);
            if (from.getDistances().count(to.getName()) != 0) {
                result += from.getDistances().at(to.getName());
            } else {
                result += to.getDistances().at(from.getName());
            }
        }
    }
    return result;
}



























