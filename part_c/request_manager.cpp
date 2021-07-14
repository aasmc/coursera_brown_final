#include "request_manager.h"
#include "sstream"
#include "unordered_map"

namespace request {
    using namespace std;

    struct AddBusRequest : ModifyRequest {
        AddBusRequest() : ModifyRequest(ModifyRequest::Type::ADD_BUS) {};

        void ParseFrom(string_view input) override {
            auto[number, line] = utils::SplitTwoStrict(input, ":");
            bus.setNumber(string(number));
            auto[isCircular, names] = utils::splitBusLine(line.value());
            bus.setCircular(isCircular);
            for (const auto &name : names) {
                bus.addBusStop(string(name));
            }
        }

        void Process(StationManager &stationManager) override {
            stationManager.addBus(bus);
        }

        Bus bus{};
    };

    struct AddBusStopRequest : ModifyRequest {
        AddBusStopRequest() : ModifyRequest(ModifyRequest::Type::ADD_STOP) {};

        void ParseFrom(string_view input) override {
            utils::trimStart(input);

            auto pos = input.find_first_of(':');
            string name;
            if (pos == input.npos) {
                throw invalid_argument("Incorrect line");
            }
            name = input.substr(0, pos);
            double latitude, longitude;
            input.remove_prefix(pos + 1);
            istringstream stream((string(input)));
            stream >> latitude;
            stream.ignore(1);
            stream >> longitude;
            stop.setName(name);
            stop.setLatitude(latitude);
            stop.setLongitude(longitude);
            // consume comma and space after longitude
            stream.ignore(2);
            string distance_line;
            getline(stream, distance_line);
            if (!distance_line.empty()) {
                stop.setDistances(utils::splitBusStopDistanceLine(distance_line));
            }
        }

        void Process(StationManager &stationManager) override {
            stationManager.addBusStop(stop);
        }

        BusStop stop{};
    };

    struct ShowInfoForBusRequest : ReadRequest<string> {

        ShowInfoForBusRequest() : ReadRequest(GetRequest::Type::BUS) {};

        void ParseFrom(string_view input) override {
            utils::trimStart(input);
            bus_number = string(input);
        }

        string Process(const StationManager &stationManager) const override {
            return stationManager.showInfoForBus(bus_number);
        }

        string bus_number;
    };

    struct ShowInfoForBusStopRequest : ReadRequest<string> {

        ShowInfoForBusStopRequest() : ReadRequest(GetRequest::Type::STOP) {};

        void ParseFrom(string_view input) override {
            utils::trimStart(input);
            bus_stop = string(input);
        }

        string Process(const StationManager &stationManager) const override {
            return stationManager.showInfoForStop(bus_stop);
        }

        string bus_stop;
    };

    ModifyRequestHolder ModifyRequest::Create(ModifyRequest::Type type) {
        switch (type) {
            case Type::ADD_BUS:
                return make_unique<AddBusRequest>();
            case Type::ADD_STOP:
                return make_unique<AddBusStopRequest>();
            default:
                return nullptr;
        }
    }

    GetRequestHolder GetRequest::Create(GetRequest::Type type) {
        switch (type) {
            case Type::BUS:
                return make_unique<ShowInfoForBusRequest>();
            case Type::STOP:
                return make_unique<ShowInfoForBusStopRequest>();
            default:
                return nullptr;
        }
    }

    std::optional<ModifyRequest::Type> ConvertModifyRequestTypeFromString(std::string_view type_str) {
        if (const auto it = STR_TO_MODIFY_REQUEST_TYPE.find(type_str);
                it != STR_TO_MODIFY_REQUEST_TYPE.end()) {
            return it->second;
        } else {
            return nullopt;
        }
    }

    std::optional<GetRequest::Type> ConvertGetRequestTypeFromString(std::string_view type_str) {
        if (const auto it = STR_TO_GET_REQUEST_TYPE.find(type_str);
                it != STR_TO_GET_REQUEST_TYPE.end()) {
            return it->second;
        } else {
            return nullopt;
        }
    }

    ModifyRequestHolder ParseModifyRequest(std::string_view request_str) {
        const auto request_type = ConvertModifyRequestTypeFromString(utils::ReadToken(request_str));
        if (!request_type) {
            return nullptr;
        }
        ModifyRequestHolder request = ModifyRequest::Create(*request_type);
        if (request) {
            request->ParseFrom(request_str);
        }
        return request;
    }

    GetRequestHolder ParseGetRequest(std::string_view request_str) {
        const auto request_type = ConvertGetRequestTypeFromString(utils::ReadToken(request_str));
        if (!request_type) {
            return nullptr;
        }
        GetRequestHolder request = GetRequest::Create(*request_type);
        if (request) {
            request->ParseFrom(request_str);
        }
        return request;
    }

    RequestManager::RequestManager(const StationManager &stationManager_) : stationManager(stationManager_) {}

    vector<GetRequestHolder> RequestManager::ReadGetRequests(istream &in_stream) {
        const size_t request_count = utils::ReadNumberOnLine<size_t>(in_stream);

        vector<GetRequestHolder> requests;
        requests.reserve(request_count);
        for (size_t i = 0; i < request_count; ++i) {
            string request_str;
            getline(in_stream, request_str);
            if (auto request = ParseGetRequest(request_str)) {
                requests.push_back(move(request));
            }
        }
        return requests;
    }

    vector<string> RequestManager::ProcessGetRequests(const vector<GetRequestHolder> &requests) {
        vector<string> responses;
        for (const auto &request_holder : requests) {
            if (request_holder->type == GetRequest::Type::BUS) {
                const auto &request = static_cast<const ShowInfoForBusRequest &>(*request_holder);
                responses.push_back(request.Process(stationManager));
            } else if (request_holder->type == GetRequest::Type::STOP) {
                const auto &request = static_cast<const ShowInfoForBusStopRequest &>(*request_holder);
                responses.push_back(request.Process(stationManager));
            }
        }
        return responses;
    }


    vector<ModifyRequestHolder> RequestManager::ReadModifyRequests(istream &in_stream) {
        const size_t request_count = utils::ReadNumberOnLine<size_t>(in_stream);

        vector<ModifyRequestHolder> requests;
        requests.reserve(request_count);
        for (size_t i = 0; i < request_count; ++i) {
            string request_str;
            getline(in_stream, request_str);
            if (auto request = ParseModifyRequest(request_str)) {
                requests.push_back(move(request));
            }
        }
        return requests;
    }

    void RequestManager::ProcessModifyRequests(const vector<ModifyRequestHolder> &requests) {
        for (const auto &request_holder : requests) {
            if (request_holder->type == ModifyRequest::Type::ADD_BUS) {
                auto &request = static_cast<AddBusRequest &>(*request_holder);
                request.Process(stationManager);
            } else if (request_holder->type == ModifyRequest::Type::ADD_STOP) {
                auto &request = static_cast<AddBusStopRequest &>(*request_holder);
                request.Process(stationManager);
            }
        }
    }

    void RequestManager::HandleModifyRequests(std::istream &in_stream) {
        ProcessModifyRequests(ReadModifyRequests(in_stream));
    }

    std::vector<std::string> RequestManager::HandleGetRequests(std::istream &in_stream) {
        return ProcessGetRequests(ReadGetRequests(in_stream));
    }

    void RequestManager::PrintGetResponses(const vector<string> &responses, ostream &stream) {
        for (const auto &line : responses) {
            stream << line << endl;
        }
    }
}
















