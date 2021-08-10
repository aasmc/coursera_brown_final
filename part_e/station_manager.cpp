#include "station_manager.h"
#include "sstream"
#include "stdexcept"
#include "iomanip"

using namespace std;

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

std::string StationManager::showRouteFromTo(const std::string &from, const std::string &to, int request_id) const {
    const auto routeDescription = getRouteDescription(from, to);

    ostringstream out;

    out << "{";
    if (routeDescription) {

        double totalTime = routeDescription->totalTime;

        out << "\"request_id\":" << request_id << "," <<
            "\"total_time\":" << totalTime << "," <<
            "\"items\":" << "[";

        bool first = true;
        for (const auto &event : routeDescription->events) {
            if (holds_alternative<Trip>(event)) {
                if (!first) {
                    out << ",";
                }
                first = false;
                const Trip &trip = get<Trip>(event);
                out << "{" <<
                    R"("type":"Bus",)" <<
                    "\"bus\":" << "\"" << trip.busNumber << "\"," <<
                    "\"time\":" << trip.time << "," <<
                    "\"span_count\":" << trip.spanCount <<
                    "}";
            } else {
                if (!first) {
                    out << ",";
                }
                first = false;
                const Wait &wait = get<Wait>(event);
                out << "{" <<
                    R"("type": "Wait",)" <<
                    "\"stop_name\":" << "\"" << wait.stopName << "\"," <<
                    "\"time\":" << wait.time <<
                    "}";
            }
        }
        out << "]";

    } else {
        out << "\"request_id\":" << request_id << ","
            << "\"error_message\":" << "\"not found\"";
    }
    out << "}";

    return out.str();
}

void StationManager::setBusVelocity(double busVelocity_) {
    busVelocity = busVelocity_;
}

void StationManager::setWaitTime(double waitTime_) {
    waitTime = waitTime_;
}

double StationManager::getBusVelocity() const {
    return busVelocity;
}

double StationManager::getBusWaitTime() const {
    return waitTime;
}

const std::unordered_map<std::string, BusStop> &StationManager::getBusStops() const {
    return busStops;
}

const std::unordered_map<std::string, Bus> &StationManager::getBuses() const {
    return buses;
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
    return result;
}

void StationManager::initializeGraph() {
    vertexNames.resize(busStops.size() * 2);
    graph = make_unique<Graph::DirectedWeightedGraph<double>>(busStops.size() * 2);
    addVertices();
    addEdges();
    router = make_unique<Graph::Router<double>>(*graph);
}

void StationManager::addVertices() {
    // condition is to start graph indices from 0
    size_t id = 0;
    // traverse all forward_stops
    for (const auto&[stopName, stops] : busStops) {
        // each stop can be either outgoing or incoming vertex in a DAG
        auto &vertexId = vertexIds[stopName];
        // set incoming vertex id
        vertexId.incoming = id++;
        // set outgoing vertex id
        vertexId.outgoing = id++;
        // save the name of the stop at the incoming and outgoing indices
        // to create a reverse index
        vertexNames[vertexId.incoming] = stopName;
        vertexNames[vertexId.outgoing] = stopName;
        // initially add WaitEdges with amount of time to wait = settings.waitTime
        totalEdges.push_back(WaitEdge{});
        graph->AddEdge(Graph::Edge<double>{
                .from = vertexId.outgoing,
                .to = vertexId.incoming,
                .weight = waitTime
        });
    }
}

void StationManager::addEdges() {
    // traverse all buses
    for (const auto&[busNumber, bus] : buses) {
        // get the number of forward_stops of the bus
        const auto numberOfStops = bus.getBusStops().size();
        if (numberOfStops <= 1) {
            continue;
        }
        // traverse all forward_stops
        for (size_t start = 0; start + 1 < numberOfStops; ++start) {
            // get the name of the starting stop
            const std::string &fromStop = bus.getBusStops()[start];
            // shows that the bus has arrived into the stop
            const size_t startVertex = vertexIds[fromStop].incoming;
            int routeDistance = 0;
            // calculate route distance from start to finish where finish
            // is all the next forward_stops one by one until the end of the route
            // thus we calculate on iteration 1 -  complete route distance,
            // on iteration 2 - route distance from stop 2 to the end of the route,
            // on iteration 3 - route distance from stop 3 to the end of the route etc.
            for (size_t finish = start + 1; finish < numberOfStops; ++finish) {
                const std::string &finishStopName = bus.getBusStops()[finish];
                // shows that the bus is going out to the stop
                size_t finishVertex = vertexIds[finishStopName].outgoing;
                routeDistance += busStops.at(bus.getBusStops()[finish - 1]).computeRoadDistanceTo(
                        busStops.at(bus.getBusStops()[finish])
                );
                // add the Edge that shows how many forward_stops a bus has passed and the bus number
                // and calculate the time it has taken for the bus to get from start stop to end stop
                // in minutes
                totalEdges.push_back(BusEdge{
                        .busNumber = bus.getNumber(),
                        .spanCount = finish - start
                });
                double time = routeDistance * 1.0 / (busVelocity * 1000 / 60);
                graph->AddEdge(Graph::Edge<double>{
                        .from = startVertex,
                        .to = finishVertex,
                        .weight = time
                });
            }
        }
    }
}

std::optional<StationManager::RouteDescription> StationManager::getRouteDescription(const std::string &from,
                                                                                    const std::string &to) const {
    size_t vertexFrom = vertexIds.at(from).outgoing;
    size_t vertexTo = vertexIds.at(to).outgoing;
    // try to build the route by the Router
    const auto route = router->BuildRoute(vertexFrom, vertexTo);
    if (!route) {
        return nullopt;
    }

    // router gets the total time taken
    double totalTime = route->weight;
    auto numberOfEdges = route->edge_count;
    RouteDescription description;
    description.totalTime = totalTime;
    description.events.reserve(numberOfEdges);
    auto routeId = route->id;
    // traverse all edges returned by the router
    for (int idx = 0; idx < numberOfEdges; ++idx) {
        // get the edge id
        auto edgeId = router->GetRouteEdge(routeId, idx);
        // get edge from the graph
        const auto &edge = graph->GetEdge(edgeId);
        // edge may be of two types: WaitEdge and BusEdge
        const auto &edgeType = totalEdges[edgeId];
        // if BusEdge
        if (holds_alternative<BusEdge>(edgeType)) {
            // get the edge from variant
            const BusEdge &busType = get<BusEdge>(edgeType);
            // add the Trip to the events vector of the RouteDescription
            description.events.push_back(Trip{
                    .busNumber = busType.busNumber,
                    .time = edge.weight,
                    .spanCount = busType.spanCount
            });
        } else { // edge is WaitEdge
            size_t vertexId = edge.from;
            description.events.push_back(Wait{
                    .stopName = vertexNames[vertexId],
                    .time = edge.weight
            });
        }
    }
    router->ReleaseRoute(routeId);
    return description;
}


























