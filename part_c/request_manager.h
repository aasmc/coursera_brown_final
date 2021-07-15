//#pragma once
//
//#include "station_manager.h"
//#include "string_view"
//#include "optional"
//#include "utils.h"
//#include "unordered_map"
//#include "memory"
//
//namespace request {
//
//    struct ModifyRequest;
//    using ModifyRequestHolder = std::unique_ptr<ModifyRequest>;
//
//    struct ModifyRequest {
//        enum class Type {
//            ADD_BUS,
//            ADD_STOP
//        };
//
//        ModifyRequest(Type type) : type(type) {}
//
//        static ModifyRequestHolder Create(Type type);
//
//        virtual void ParseFrom(std::string_view input) = 0;
//
//        virtual void Process(StationManager &stationManager) = 0;
//
//        virtual ~ModifyRequest() = default;
//
//        const Type type;
//    };
//
//    const std::unordered_map<std::string_view, ModifyRequest::Type> STR_TO_MODIFY_REQUEST_TYPE = {
//            {"Bus",  ModifyRequest::Type::ADD_BUS},
//            {"Stop", ModifyRequest::Type::ADD_STOP}
//    };
//
//    struct GetRequest;
//    using GetRequestHolder = std::unique_ptr<GetRequest>;
//
//    struct GetRequest {
//        enum class Type {
//            BUS,
//            STOP
//        };
//
//        GetRequest(GetRequest::Type type_) : type(type_) {};
//
//        static GetRequestHolder Create(Type type);
//
//        virtual void ParseFrom(std::string_view input) = 0;
//
//        virtual ~GetRequest() = default;
//
//        const GetRequest::Type type;
//    };
//
//    const std::unordered_map<std::string_view, GetRequest::Type> STR_TO_GET_REQUEST_TYPE = {
//            {"Bus",  GetRequest::Type::BUS},
//            {"Stop", GetRequest::Type::STOP}
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
//    ModifyRequestHolder ParseModifyRequest(std::string_view request_str);
//
//    GetRequestHolder ParseGetRequest(std::string_view request_str);
//
//    class RequestManager {
//    private:
//        StationManager stationManager;
//
//        std::vector<ModifyRequestHolder> ReadModifyRequests(std::istream &in_stream = std::cin);
//
//        std::vector<GetRequestHolder> ReadGetRequests(std::istream &in_stream = std::cin);
//
//        std::vector<std::string> ProcessGetRequests(const std::vector<GetRequestHolder> &requests);
//
//        void ProcessModifyRequests(const std::vector<ModifyRequestHolder> &requests);
//
//    public:
//
//        RequestManager(const StationManager &stationManager_);
//
//        void HandleModifyRequests(std::istream &in_stream = std::cin);
//
//        std::vector<std::string> HandleGetRequests(std::istream &in_stream = std::cin);
//
//        void PrintGetResponses(const std::vector<std::string> &responses, std::ostream &stream = std::cout);
//    };
//
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
