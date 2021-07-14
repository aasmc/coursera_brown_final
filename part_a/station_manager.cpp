#include "station_manager.h"
#include "sstream"
#include "stdexcept"
#include "iomanip"

std::pair<std::string_view, std::optional<std::string_view>>
SplitTwoStrict(std::string_view s, std::string_view delimiter) {
    const size_t pos = s.find(delimiter);
    if (pos == s.npos) {
        return {s, std::nullopt};
    } else {
        return {s.substr(0, pos), s.substr(pos + delimiter.length())};
    }
}

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter) {
    const auto[lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    return {lhs, rhs_opt.value_or("")};
}

std::string_view ReadToken(std::string_view &s, std::string_view delimiter) {
    const auto[lhs, rhs] = SplitTwo(s, delimiter);
    s = rhs;
    return lhs;
}


void trimStart(std::string_view &line) {
    while (line[0] == ' ') {
        line.remove_prefix(1);
    }
}

void trimEnd(std::string_view &line) {
    auto pos = line.size() - 1;
    while (line[pos] == ' ') {
        line.remove_suffix(pos - 1);
    }
}

std::pair<bool, std::vector<std::string_view>> split(std::string_view line) {
    // consume delimiter that is left after splitting the line
    line.remove_prefix(1);
    bool isCircular = false;
    std::vector<std::string_view> result;
    trimStart(line);
    auto pos = line.find_first_of('>');
    if (pos != line.npos) {
        isCircular = true;
    } else {
        pos = line.find_first_of('-');
    }

    while (pos != line.npos) {
        result.push_back(line.substr(0, pos - 1));
        line.remove_prefix(pos + 2);
        if (isCircular) {
            pos = line.find('>');
        } else {
            pos = line.find('-');
        }
    }
    // don't forget to push_back the last segment
    result.push_back(line.substr(0));
    return {isCircular, result};
}

int ConvertToInt(std::string_view str) {
    // use std::from_chars when available to get rid of string copy
    size_t pos;
    const int result = stoi(std::string(str), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
        throw std::invalid_argument(error.str());
    }
    return result;
}

void StationManager::readBusStop(std::string_view line) {
    trimStart(line);
    auto pos = line.find_first_of(':');
    std::string name;
    if (pos == line.npos) {
        throw std::invalid_argument("Incorrect line");
    }
    name = line.substr(0, pos);
    double latitude, longitude;
    line.remove_prefix(pos + 1);
    std::istringstream str((std::string(line)));
    str >> latitude;
    str.ignore(1);
    str >> longitude;
    busStops[name] = BusStop{name, latitude, longitude};
}

void StationManager::readBus(std::string_view line_) {
    Bus bus;
    auto[number, line] = SplitTwoStrict(line_, ":");
    bus.setNumber(std::string(number));
    auto[isCircular, names] =  split(line.value());
    bus.setCircular(isCircular);
    for (const auto &name : names) {
        bus.addBusStop(std::string(name));
    }
    buses[std::string(number)] = bus;
}

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
           calculateRouteLength(number) << " route length" << std::endl;
    return output.str();
}





























