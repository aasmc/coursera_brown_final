//#include "json.h"
//
//using namespace std;
//
//namespace Json {
//
//    Document::Document(Node root) : root(move(root)) {
//    }
//
//    const Node &Document::GetRoot() const {
//        return root;
//    }
//
//    Node LoadNode(istream &input);
//
//    Node LoadArray(istream &input) {
//        vector<Node> result;
//
//        for (char c; input >> c && c != ']';) {
//            if (c != ',') {
//                input.putback(c);
//            }
//            result.push_back(LoadNode(input));
//        }
//
//        return Node(move(result));
//    }
//
//    Node LoadBool(istream &input) {
//        string str;
//        char c;
//        input >> c;
//        while (isalpha(c)) {
//            str += c;
//            input >> c;
//        }
//        if (c == ',' || c == '}') {
//            input.putback(c);
//        }
//        if (str == "false") {
//            return Node(false);
//        } else {
//            return Node(true);
//        }
//    }
//
//    Node LoadDouble(istream &input) {
//        string line;
//        char ch;
//        input >> ch;
//        while (isdigit(ch) || ch == '-' || ch == '.') {
//            line += ch;
//            input >> ch;
//        }
//        input.putback(ch);
//        return Node(stod(line));
//    }
//
//    Node LoadString(istream &input) {
//        string line;
//        getline(input, line, '"');
//        return Node(move(line));
//    }
//
//    Node LoadDict(istream &input) {
//        map<string, Node> result;
//
//        for (char c; input >> c && c != '}';) {
//            if (c == ',') {
//                input >> c;
//            }
//
//            string key = LoadString(input).AsString();
//            input >> c;
//            result.emplace(move(key), LoadNode(input));
//        }
//
//        return Node(move(result));
//    }
//
//    Node LoadNode(istream &input) {
//        char c;
//        input >> c;
//        if (c == '[') {
//            return LoadArray(input);
//        } else if (c == '{') {
//            return LoadDict(input);
//        } else if (c == '"') {
//            return LoadString(input);
//        } else if (isalpha(c)) {
//            input.putback(c);
//            return LoadBool(input);
//        } else {
//            input.putback(c);
//            return LoadDouble(input);
//        }
//    }
//
//    Document Load(istream &input) {
//        return Document{LoadNode(input)};
//    }
//}
