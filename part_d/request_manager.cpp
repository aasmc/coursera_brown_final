//#include "request_manager.h"
//#include "sstream"
//#include "unordered_map"
//
//namespace request {
//    using namespace std;
//
//    struct AddBusRequest : ModifyRequest {
//        AddBusRequest() : ModifyRequest(ModifyRequest::Type::ADD_BUS) {};
//
//        void ParseFromJson(const Json::Node &node) override {
//
//            const auto &busInfo = node.AsMap();
//            const auto &number = busInfo.at("name").AsString();
//            bus.setNumber(number);
//            bus.setCircular(busInfo.at("is_roundtrip").AsBool());
//            const auto &forward_stops = busInfo.at("forward_stops").AsArray();
//            for (const auto &stop : forward_stops) {
//                bus.addBusStop(stop.AsString());
//            }
//        }
//
//        void Process(StationManager &stationManager) override {
//            stationManager.addBus(bus);
//        }
//
//        Bus bus{};
//    };
//
//    struct AddBusStopRequest : ModifyRequest {
//        AddBusStopRequest() : ModifyRequest(ModifyRequest::Type::ADD_STOP) {};
//
//        void ParseFromJson(const Json::Node &node) override {
//
//            const auto &stopInfo = node.AsMap();
//            stop.setName(stopInfo.at("name").AsString());
//            stop.setLatitude(stopInfo.at("latitude").AsDouble());
//            stop.setLongitude(stopInfo.at("longitude").AsDouble());
//            const auto &distances = stopInfo.at("road_distances").AsMap();
//            unordered_map<string, int> result;
//            for (const auto&[stop, distance] : distances) {
//                result[stop] = static_cast<int>(distance.AsDouble());
//            }
//            stop.setDistances(result);
//        }
//
//        void Process(StationManager &stationManager) override {
//            stationManager.addBusStop(stop);
//        }
//
//        BusStop stop{};
//    };
//
//    struct ShowInfoForBusRequest : ReadRequest<string> {
//
//        ShowInfoForBusRequest() : ReadRequest(GetRequest::Type::BUS) {};
//
//        void ParseFromJson(const Json::Node &node) override {
//            const auto &request_info = node.AsMap();
//            bus_number = request_info.at("name").AsString();
//            request_id = static_cast<int>(request_info.at("id").AsDouble());
//        }
//
//        string Process(const StationManager &stationManager) const override {
//            return stationManager.showInfoForBus(bus_number, request_id);
//        }
//
//        string bus_number;
//        int request_id;
//    };
//
//    struct ShowInfoForBusStopRequest : ReadRequest<string> {
//
//        ShowInfoForBusStopRequest() : ReadRequest(GetRequest::Type::STOP) {};
//
//        void ParseFromJson(const Json::Node &node) override {
//            const auto &request_info = node.AsMap();
//            bus_stop = request_info.at("name").AsString();
//            request_id = static_cast<int>(request_info.at("id").AsDouble());
//        }
//
//        string Process(const StationManager &stationManager) const override {
//            return stationManager.showInfoForStop(bus_stop, request_id);
//        }
//
//        string bus_stop;
//        int request_id;
//    };
//
//    ModifyRequestHolder ModifyRequest::Create(ModifyRequest::Type type) {
//        switch (type) {
//            case Type::ADD_BUS:
//                return make_unique<AddBusRequest>();
//            case Type::ADD_STOP:
//                return make_unique<AddBusStopRequest>();
//            default:
//                return nullptr;
//        }
//    }
//
//    GetRequestHolder GetRequest::Create(GetRequest::Type type) {
//        switch (type) {
//            case Type::BUS:
//                return make_unique<ShowInfoForBusRequest>();
//            case Type::STOP:
//                return make_unique<ShowInfoForBusStopRequest>();
//            default:
//                return nullptr;
//        }
//    }
//
//    std::optional<ModifyRequest::Type> ConvertModifyRequestTypeFromString(std::string_view type_str) {
//        if (const auto it = STR_TO_MODIFY_REQUEST_TYPE.find(type_str);
//                it != STR_TO_MODIFY_REQUEST_TYPE.end()) {
//            return it->second;
//        } else {
//            return nullopt;
//        }
//    }
//
//    std::optional<GetRequest::Type> ConvertGetRequestTypeFromString(std::string_view type_str) {
//        if (const auto it = STR_TO_GET_REQUEST_TYPE.find(type_str);
//                it != STR_TO_GET_REQUEST_TYPE.end()) {
//            return it->second;
//        } else {
//            return nullopt;
//        }
//    }
//
//    ModifyRequestHolder ParseModifyRequest(const Json::Node &node) {
//        const auto &request_info = node.AsMap();
//        const auto request_type = ConvertModifyRequestTypeFromString(request_info.at("type").AsString());
//        if (!request_type) {
//            return nullptr;
//        }
//        ModifyRequestHolder request = ModifyRequest::Create(*request_type);
//        if (request) {
//            request->ParseFromJson(node);
//        }
//        return request;
//    }
//
//    GetRequestHolder ParseGetRequest(const Json::Node &node) {
//        const auto &request_info = node.AsMap();
//        const auto request_type = ConvertGetRequestTypeFromString(request_info.at("type").AsString());
//        if (!request_type) {
//            return nullptr;
//        }
//        GetRequestHolder request = GetRequest::Create(*request_type);
//        if (request) {
//            request->ParseFromJson(node);
//        }
//        return request;
//    }
//
//    RequestManager::RequestManager(const StationManager &stationManager_) : stationManager(stationManager_) {}
//
//    vector<GetRequestHolder> RequestManager::ReadGetRequests(const std::vector<Json::Node> &requests) {
//
//        const size_t request_count = requests.size();
//
//        vector<GetRequestHolder> get_requests;
//        get_requests.reserve(request_count);
//        for (const auto &node : requests) {
//            if (auto request = ParseGetRequest(node)) {
//                get_requests.push_back(move(request));
//            }
//        }
//        return get_requests;
//    }
//
//    vector<string> RequestManager::ProcessGetRequests(const vector<GetRequestHolder> &requests) {
//        vector<string> responses;
//        for (const auto &request_holder : requests) {
//            if (request_holder->type == GetRequest::Type::BUS) {
//                const auto &request = static_cast<const ShowInfoForBusRequest &>(*request_holder);
//                responses.push_back(request.Process(stationManager));
//            } else if (request_holder->type == GetRequest::Type::STOP) {
//                const auto &request = static_cast<const ShowInfoForBusStopRequest &>(*request_holder);
//                responses.push_back(request.Process(stationManager));
//            }
//        }
//        return responses;
//    }
//
//
//    vector<ModifyRequestHolder> RequestManager::ReadModifyRequests(const std::vector<Json::Node> &requests) {
//
//        const size_t request_count = requests.size();
//
//        vector<ModifyRequestHolder> mod_requests;
//        mod_requests.reserve(request_count);
//        for (const auto& node : requests) {
//            if (auto request = ParseModifyRequest(node)) {
//                mod_requests.push_back(move(request));
//            }
//        }
//        return mod_requests;
//    }
//
//    void RequestManager::ProcessModifyRequests(const vector<ModifyRequestHolder> &requests) {
//        for (const auto &request_holder : requests) {
//            if (request_holder->type == ModifyRequest::Type::ADD_BUS) {
//                auto &request = static_cast<AddBusRequest &>(*request_holder);
//                request.Process(stationManager);
//            } else if (request_holder->type == ModifyRequest::Type::ADD_STOP) {
//                auto &request = static_cast<AddBusStopRequest &>(*request_holder);
//                request.Process(stationManager);
//            }
//        }
//    }
//
//    void RequestManager::HandleModifyRequests(const std::vector<Json::Node> &requests) {
//        ProcessModifyRequests(ReadModifyRequests(requests));
//    }
//
//    std::vector<std::string> RequestManager::HandleGetRequests(const std::vector<Json::Node> &requests) {
//        return ProcessGetRequests(ReadGetRequests(requests));
//    }
//
//    void RequestManager::PrintGetResponses(const vector<string> &responses, ostream &stream) {
//        stream << "[";
//        bool first = true;
//        for (const auto &line : responses) {
//            if (!first) {
//                stream << "," << line;
//            } else {
//                stream << line;
//                first = false;
//            }
//        }
//        stream << "]";
//    }
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
