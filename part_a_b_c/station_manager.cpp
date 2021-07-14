//#include "station_manager.h"
//#include "sstream"
//#include "stdexcept"
//#include "iomanip"
//
//double StationManager::calculateGeographicRouteLength(const std::string &number) const {
//    if (buses.count(number) == 0) {
//        throw std::invalid_argument("No such bus: " + number);
//    }
//    const Bus &bus = buses.at(number);
//    if (bus.getTotalNumberOfStops() < 2) {
//        return 0;
//    }
//    const auto &stops = bus.getBusStops();
//    double result = 0;
//    for (int i = 0; i < stops.size() - 1; ++i) {
//        result += busStops.at(stops[i]).computeGeographicDistance(busStops.at(stops[i + 1]));
//    }
//    if (!bus.isBusCircular()) {
//        result *= 2;
//    }
//    return result;
//}
//
//std::string StationManager::showInfoForBus(const std::string &number) const {
//    std::ostringstream output;
//    if (buses.count(number) == 0) {
//        output << "Bus " << number << ": not found"; /*<< std::endl*/;
//        return output.str();
//    }
//    const Bus &bus = buses.at(number);
//    output << "Bus " << bus.getNumber() << ": " << bus.getNumberOfStopsOnRoute()
//           << " stops on route, " << bus.getUniqueStops() << " unique stops, " <<
//           std::setprecision(6) <<
//           calculateGeographicRouteLength(number) << " route length";
//    return output.str();
//}
//
//void StationManager::addBusStop(const BusStop &busStop) {
//    auto &stop = busStops[busStop.getName()];
//    stop.setName(busStop.getName());
//    stop.setLatitude(busStop.getLatitude());
//    stop.setLongitude(busStop.getLongitude());
//}
//
//void StationManager::addBus(const Bus &bus) {
//    buses[bus.getNumber()] = bus;
//    const auto &stops = bus.getBusStops();
//    for (const auto &stop : stops) {
//        busStops[stop].addBus(bus.getNumber());
//    }
//}
//
//std::string StationManager::showInfoForStop(const std::string &stop) const {
//    std::ostringstream output;
//    output << "Stop " << stop << ": ";
//    if (busStops.count(stop) == 0) {
//        output <<"not found";
//    } else if (busStops.at(stop).getBusNumbers().empty()) {
//        output << "no buses";
//    } else  {
//        const auto& busNumbers = busStops.at(stop).getBusNumbers();
//        output << "buses ";
//        bool first = true;
//        for(const auto& busNumber : busNumbers) {
//            if (!first) {
//                output << ' ' << busNumber;
//            } else {
//                output << busNumber;
//                first = false;
//            }
//        }
//    }
//    return output.str();
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
