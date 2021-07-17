#include <iostream>
#include <sstream>
#include "request_manager.h"
#include "json.h"

using namespace std;
using namespace request;
using namespace Json;


int main() {

    Document doc = Load(cin);
    StationManager stationManager;
    RequestManager requestManager{move(stationManager)};

    const auto &root = doc.GetRoot().AsMap();
    const auto &settings = root.at("routing_settings");
    const auto &create_requests = root.at("base_requests").AsArray();
    const auto &stats_requests = root.at("stat_requests").AsArray();

    requestManager.HandleSettingsRequest(settings);
    requestManager.HandleModifyRequests(create_requests);
    requestManager.initializeGraph();
    const auto &resp = requestManager.HandleGetRequests(stats_requests);
    requestManager.PrintGetResponses(resp,  cout);

    return 0;
}
