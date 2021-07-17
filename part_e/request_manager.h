//#pragma once
//
//#include "station_manager.h"
//#include "string_view"
//#include "optional"
//#include "utils.h"
//#include "unordered_map"
//#include "memory"
//#include "json.h"
//
//namespace request {
//
//    struct ModifyRequest;
//    using ModifyRequestHolder = std::unique_ptr<ModifyRequest>;
//
//    struct ModifyRequest {
//        enum class Type {
//            ADD_BUS,
//            ADD_STOP,
//            ADD_SETTINGS
//        };
//
//        ModifyRequest(Type type) : type(type) {}
//
//        static ModifyRequestHolder Create(Type type);
//
//        virtual void ParseFromJson(const Json::Node &node) = 0;
//
//        virtual void Process(StationManager &stationManager) = 0;
//
//        virtual ~ModifyRequest() = default;
//
//        const Type type;
//    };
//
//    const std::unordered_map<std::string_view, ModifyRequest::Type> STR_TO_MODIFY_REQUEST_TYPE = {
//            {"Bus",              ModifyRequest::Type::ADD_BUS},
//            {"Stop",             ModifyRequest::Type::ADD_STOP},
//            {"routing_settings", ModifyRequest::Type::ADD_SETTINGS}
//    };
//
//    struct GetRequest;
//    using GetRequestHolder = std::unique_ptr<GetRequest>;
//
//    struct GetRequest {
//        enum class Type {
//            BUS,
//            STOP,
//            ROUTE
//        };
//
//        GetRequest(GetRequest::Type type_) : type(type_) {};
//
//        static GetRequestHolder Create(Type type);
//
//        virtual void ParseFromJson(const Json::Node &node) = 0;
//
//        virtual ~GetRequest() = default;
//
//        const GetRequest::Type type;
//    };
//
//    const std::unordered_map<std::string_view, GetRequest::Type> STR_TO_GET_REQUEST_TYPE = {
//            {"Bus",   GetRequest::Type::BUS},
//            {"Stop",  GetRequest::Type::STOP},
//            {"Route", GetRequest::Type::ROUTE}
//    };
//
//    template<class ResultType>
//    struct ReadRequest : GetRequest {
//        using GetRequest::GetRequest;
//
//        virtual ResultType Process(const StationManager &stationManager) const = 0;
//    };
//
//
//    std::optional<ModifyRequest::Type> ConvertModifyRequestTypeFromString(std::string_view type_str);
//
//    std::optional<GetRequest::Type> ConvertGetRequestTypeFromString(std::string_view type_str);
//
//    ModifyRequestHolder ParseModifyRequest(const Json::Node &node);
//
//    GetRequestHolder ParseGetRequest(const Json::Node &node);
//
//    ModifyRequestHolder ParseSettingsRequest(const Json::Node &node);
//
//    class RequestManager {
//    private:
//        StationManager stationManager;
//
//        std::vector<ModifyRequestHolder> ReadModifyRequests(const std::vector<Json::Node> &requests);
//
//        std::vector<GetRequestHolder> ReadGetRequests(const std::vector<Json::Node> &requests);
//
//        std::vector<std::string> ProcessGetRequests(const std::vector<GetRequestHolder> &requests);
//
//        void ProcessSettingsRequest(const ModifyRequestHolder &request);
//
//        void ProcessModifyRequests(const std::vector<ModifyRequestHolder> &requests);
//
//    public:
//
//        RequestManager(StationManager stationManager_);
//
//        void HandleModifyRequests(const std::vector<Json::Node> &requests);
//
//        std::vector<std::string> HandleGetRequests(const std::vector<Json::Node> &requests);
//
//        void HandleSettingsRequest(const Json::Node &request);
//
//        void initializeGraph();
//
//        void PrintGetResponses(const std::vector<std::string> &responses, std::ostream &stream = std::cout);
//
//    };
//
//
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
