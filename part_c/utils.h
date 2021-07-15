//#pragma once
//#include "vector"
//#include <utility>
//#include <string_view>
//#include <optional>
//#include "unordered_map"
//#include "iostream"
//
//namespace utils {
//
//    std::pair<std::string_view, std::optional<std::string_view>>
//    SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");
//
//    std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");
//
//    std::string_view ReadToken(std::string_view &s, std::string_view delimiter = " ");
//
//    void trimStart(std::string_view &line);
//
//    void trimEnd(std::string_view &line);
//
//    std::pair<bool, std::vector<std::string_view>> splitBusLine(std::string_view line);
//
//    int ConvertToInt(std::string_view str);
//
//    template<typename Number>
//    Number ReadNumberOnLine(std::istream &stream);
//
//
//    template<typename Number>
//    Number ReadNumberOnLine(std::istream &stream) {
//        Number number;
//        stream >> number;
//        std::string dummy;
//        std::getline(stream, dummy);
//        return number;
//    }
//    std::vector<std::string_view> splitLineToVector(std::string_view line, std::string_view delimiter = " ");
//
//    std::unordered_map<std::string, int> splitBusStopDistanceLine(std::string_view distance_line);
//}
