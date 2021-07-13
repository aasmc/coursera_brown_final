#pragma once

#include "iostream"
#include "map"
#include "set"
#include "string"
#include "sstream"
#include "vector"
#include "unordered_map"

#define ASSERT_EQUAL(x, y) { \
    ostringstream __unique_name_os;  \
    __unique_name_os << #x << " != " << #y << ", "<< __FILE__ << ":" << __LINE__; \
    AssertEqual(x, y, __unique_name_os.str()); \
};

#define ASSERT(x) { \
    ostringstream __unique_name_os;  \
    __unique_name_os << #x << " is false, "<< __FILE__ << ":" << __LINE__; \
    Assert(x, __unique_name_os.str()); \
};

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func)



using namespace std;


// interface
template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint);

void Assert(bool b, const string &hint);

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m);

template<class K, class V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &m);


template<class T>
ostream &operator<<(ostream &os, const set<T> &s);

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s);

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name);

    ~TestRunner();

private:
    int fail_count = 0;
};

// implementation
template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw runtime_error(os.str());
    }
}

template<class TestFunc>
void TestRunner::RunTest(TestFunc func, const string &test_name) {
    try {
        func();
        cerr << test_name << " OK" << endl;
    } catch (exception& e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
        ++fail_count;
        cerr << "Unknown exception caught" << endl;
    }
}
