#include "utils.h"
#include "sstream"

namespace utils {
    using namespace std;

    std::pair<std::string_view, std::optional<std::string_view>>
    SplitTwoStrict(std::string_view s, std::string_view delimiter) {
        const size_t pos = s.find(delimiter);
        if (pos == s.npos) {
            return {s, std::nullopt};
        } else {
            return {s.substr(0, pos), s.substr(pos + delimiter.length())};
        }
    }

    std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter) {
        const auto[lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
        return {lhs, rhs_opt.value_or("")};
    }

    std::string_view ReadToken(std::string_view &s, std::string_view delimiter) {
        const auto[lhs, rhs] = SplitTwo(s, delimiter);
        s = rhs;
        return lhs;
    }

    void trimStart(std::string_view &line) {
        while (line[0] == ' ') {
            line.remove_prefix(1);
        }
    }

    void trimEnd(std::string_view &line) {
        auto pos = line.size() - 1;
        while (line[pos] == ' ') {
            line.remove_suffix(pos - 1);
        }
    }

    std::pair<bool, std::vector<std::string_view>> splitBusLine(std::string_view line) {
        // consume delimiter that is left after splitting the line
        line.remove_prefix(1);
        bool isCircular = false;
        std::vector<std::string_view> result;
        trimStart(line);
        auto pos = line.find_first_of('>');
        if (pos != line.npos) {
            isCircular = true;
        } else {
            pos = line.find_first_of('-');
        }

        while (pos != line.npos) {
            result.push_back(line.substr(0, pos - 1));
            line.remove_prefix(pos + 2);
            if (isCircular) {
                pos = line.find('>');
            } else {
                pos = line.find('-');
            }
        }
        // don't forget to push_back the last segment
        result.push_back(line.substr(0));
        return {isCircular, result};
    }


    vector<string_view> splitLineToVector(string_view line, string_view delimiter) {
        trimStart(line);
        vector<string_view> result;
        auto pos = line.find(delimiter);
        while (pos != line.npos) {
            result.push_back(line.substr(0, pos));
            line.remove_prefix(pos + 1);
            pos = line.find(delimiter);
        }
        result.push_back(line.substr(0));
        return result;
    }

    int ConvertToInt(string_view str) {
        // use std::from_chars when available to get rid of string copy
        size_t pos;
        const int result = stoi(string(str), &pos);
        if (pos != str.length()) {
            std::stringstream error;
            error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
            throw invalid_argument(error.str());
        }
        return result;
    }

    unordered_map<string, int> splitBusStopDistanceLine(string_view distance_line) {
        unordered_map<string, int> distances;
        const vector<string_view> &lines = splitLineToVector(distance_line, ",");
        for (const auto &line : lines) {
            auto[dst, to] = SplitTwo(line, "m to ");
            trimStart(dst);
            distances[string(to)] = ConvertToInt(dst);
        }
        return distances;
    }

}