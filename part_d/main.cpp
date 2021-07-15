#include <iostream>
#include "request_manager.h"
#include "json.h"
#include "fstream"

using namespace std;
using namespace request;
using namespace Json;

int main() {
//    fstream f("./routes.json");
//    fstream out("./output.json");
    Document doc = Load(cin);
    StationManager stationManager;
    RequestManager requestManager{stationManager};

    const auto &root = doc.GetRoot().AsMap();
    const auto &create_requests = root.at("base_requests").AsArray();
    const auto &stats_requests = root.at("stat_requests").AsArray();
    requestManager.HandleModifyRequests(create_requests);
    const auto &resp = requestManager.HandleGetRequests(stats_requests);
    requestManager.PrintGetResponses(resp, cout);
    return 0;
}
