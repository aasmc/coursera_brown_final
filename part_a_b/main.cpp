#include <iostream>
#include "request_manager.h"

using namespace std;
using namespace request;

int main() {
    StationManager stationManager;
    RequestManager requestManager{stationManager};

    const auto& modifyRequests = requestManager.ReadModifyRequests();
    requestManager.ProcessModifyRequests(modifyRequests);
    const auto &getRequests = requestManager.ReadGetRequests();
    const auto &results = requestManager.ProcessGetRequests(getRequests);
    requestManager.PrintGetResponses(results);
//    StationManager stationManager;
//    int q;
//    cin >> q;
//    string dummy;
//    getline(cin, dummy);
//    for (int i = 0; i < q; ++i) {
//        string line;
//        getline(cin, line);
//        auto [command, input] = SplitTwoStrict(line);
//        if (command == "Stop") {
//            if (input) {
//                stationManager.readBusStop(input.value());
//            }
//        } else if (command == "Bus") {
//            if (input) {
//                stationManager.readBus(input.value());
//            }
//        } else {
//            cout << "Unknown command" << endl;
//        }
//    }
//    int r;
//    cin >> r;
//    for (int i = 0; i < r; ++i) {
//        string command;
//        cin >> command;
//        if (command == "Bus") {
//            string number;
//            cin.ignore(1);
//            getline(cin, number);
//            cout << stationManager.showInfoForBus(number);
//        } else {
//            cout << "Unknown command" << endl;
//        }
//    }
    return 0;
}
