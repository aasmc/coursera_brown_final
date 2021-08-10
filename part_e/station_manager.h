#pragma once

#include "stop.h"
#include "bus.h"
#include "string_view"
#include "optional"
#include "unordered_map"
#include "unordered_set"
#include "iostream"
#include "memory"
#include "variant"
#include "router.h"

class StationManager {
private:
    std::unordered_map<std::string, BusStop> busStops;
    std::unordered_map<std::string , Bus> buses;
    double waitTime = 0;
    double busVelocity = 0.0;

    std::unique_ptr<Graph::Router<double>> router;
    std::unique_ptr<Graph::DirectedWeightedGraph<double>> graph;

    void addVertices();

    void addEdges();


public:

    void initializeGraph();

    const std::unordered_map<std::string, BusStop>& getBusStops() const;

    const std::unordered_map<std::string, Bus>& getBuses() const;

    void addBus(const Bus &bus);

    void addBusStop(const BusStop &busStop);

    std::string showInfoForBus(const std::string &number, int request_id) const;

    std::string showInfoForStop(const std::string &stop, int request_id) const;

    std::string showRouteFromTo(const std::string &from, const std::string &to, int request_id) const;

    double calculateGeographicRouteLength(const std::string &number) const;

    int calculateRouteLength(const std::string &number) const;

    void setWaitTime(double waitTime);

    void setBusVelocity(double busVelocity_);

    double getBusWaitTime() const;

    double getBusVelocity() const;

    struct Wait {
        std::string stopName;
        double time;
    };

    struct Trip {
        std::string busNumber;
        double time;
        size_t spanCount;
    };

    struct RouteDescription {
        double totalTime;
        using Event = std::variant<Wait, Trip>;
        std::vector<Event> events;
    };

private:
    std::optional<RouteDescription> getRouteDescription(const std::string &from, const std::string &to) const;

    struct BusEdge {
        std::string busNumber;
        size_t spanCount;
    };

    struct WaitEdge {
    };
    using Edges = std::variant<BusEdge, WaitEdge>;
    std::vector<Edges> totalEdges;

    struct VertexIds {
        size_t incoming;
        size_t outgoing;
    };

    std::unordered_map<std::string, VertexIds> vertexIds;
    std::vector<std::string> vertexNames;

};
