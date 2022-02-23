#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <deque>
#include <set>
#include <map>
#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

template<typename A, typename B> ostream& operator<<(ostream& out, pair<A, B> p) { out << "(" << p.first << ", " << p.second << ")"; return out; }
template<typename T> ostream& operator<<(ostream& out, vector<T> v) { out << "["; for (auto& x : v) out << x << ", "; out << "]"; return out; }
template<typename T> ostream& operator<<(ostream& out, deque<T> v) { out << "["; for (auto& x : v) out << x << ", "; out << "]"; return out; }
template<typename T> ostream& operator<<(ostream& out, set<T> v) { out << "{"; for (auto& x : v) out << x << ", "; out << "}"; return out; }
template<typename K, typename V> ostream& operator<<(ostream& out, map<K, V> m) { out << "{"; for (auto& e : m) out << e.first << " -> " << e.second << ", "; out << "}"; return out; }

template<typename T> T read() { T x; cin >> x; return x; }
template<typename T> vector<T> read(int intersections) { vector<T> v(intersections); for (auto& x : v) cin >> x; return v; }
template<typename A, typename B>istream& operator>>(istream& in, pair<A, B>& p) { return in >> p.first >> p.second; }

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define FOR(i, begin, end) for (int i = (begin); i < (end); i++)
#define sgn(a)     ((a) > eps ? 1 : ((a) < -eps ? -1 : 0))
#define precise(x) fixed << setprecision(x)
#define all(a) a.begin(), a.end()
#define pb push_back
#define rnd(a, b) (uniform_int_distribution<int>((a), (b))(rng))
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
std::chrono::steady_clock::time_point __clock__;
void startTime() { __clock__ = std::chrono::steady_clock::now(); }
ld getTime() {
    auto end = std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::microseconds> (end - __clock__).count();
    return ld(t) / 1e6;
}
void timeit(string msg) {
    cerr << "> " << msg << ": " << precise(6) << getTime() << endl;
}
template<typename T> inline bool maxi(T& a, T b) { return b > a ? (a = b, true) : false; }
template<typename T> inline bool mini(T& a, T b) { return b < a ? (a = b, true) : false; }
const ld PI = asin(1) * 2;
const ld eps = 1e-6;
const int oo = 2e9;
const ll OO = 2e18;
const ll MOD = 1000000007;

#define for_(i, n) for (int i = 0; i < (n); i++)
#define fori(n) for_(i, (n))
#define forj(n) for_(j, (n))
#define fork(n) for_(k, (n))
#define ford(n) for_(d, (n))

typedef void (*solverFn)();

struct Test {
    string name;
    int bestScore;
    solverFn solve;
    int currentScore;
};

Test currentTest;

// ================ MODEL ================

int clients;
vector<int> like[100000];
vector<int> dislike[100000];
vector<string> names;
set<int> pizza;

// =============== SCORING ===============

int scoreResult() {
    // todo: calculate score from current model
    return 0;
}

// =========== INPUT / OUTPUT ============

template<typename Input>
void readInput(Input &input) {
    // todo: parse model from input
}

template<typename Output>
void writeOutput(Output &output) {
    // todo: write current solution to output
}

// =======================================

string inputFolder;

void readInputFile(string testName) {
    string path = inputFolder + testName + ".txt";
    ifstream in(path);
    readInput(in);
}

void padAppend(string &str, int value, int digits) {
    if (digits == 0) {
        return;
    }
    int digit = value;
    fori(digits - 1) {
        digit /= 10;
    }
    str.push_back('0' + (digit % 10));
    padAppend(str, value, digits - 1);
}

bool writeOutputFile(string testName) {
    int score = scoreResult();
    // cout << "rescore: " << score << endl;
    if (score <= currentTest.currentScore) {
        return false;
    }
    currentTest.currentScore = score;
    cerr << "test " << currentTest.name << " scored " << score;
    if (score > currentTest.bestScore) {
        cerr << ", improved by " << score - currentTest.bestScore << endl;
        string path = testName + '_';
        padAppend(path, score, 9);
        path += ".out";
        ofstream out(path);
        writeOutput(out);
    } else {
        cerr << endl;
    }
    return true;
}

bool writeCurrentSolution() {
    return writeOutputFile(currentTest.name);
}

// ============= SOLVERS =============

namespace testA {
#include "test_a.cpp"
#ifdef USE_EVERYWHERE
#ifdef SOLVER
#error "multiple solvers have USE_EVERYWHERE"
#endif
#define SOLVER(a) testA::solveTest
#undef USE_EVERYWHERE
#endif
}

namespace testB {
#include "test_b.cpp"
#ifdef USE_EVERYWHERE
#ifdef SOLVER
#error "multiple solvers have USE_EVERYWHERE"
#endif
#define SOLVER(a) testB::solveTest
#undef USE_EVERYWHERE
#endif
}

namespace testC {
#include "test_c.cpp"
#ifdef USE_EVERYWHERE
#ifdef SOLVER
#error "multiple solvers have USE_EVERYWHERE"
#endif
#define SOLVER(a) testC::solveTest
#undef USE_EVERYWHERE
#endif
}

namespace testD {
#include "test_d.cpp"
#ifdef USE_EVERYWHERE
#ifdef SOLVER
#error "multiple solvers have USE_EVERYWHERE"
#endif
#define SOLVER(a) testD::solveTest
#undef USE_EVERYWHERE
#endif
}

namespace testE {
#include "test_e.cpp"
#ifdef USE_EVERYWHERE
#ifdef SOLVER
#error "multiple solvers have USE_EVERYWHERE"
#endif
#define SOLVER(a) testE::solveTest
#undef USE_EVERYWHERE
#endif
}

#ifndef SOLVER
#define SOLVER(a) (a)
#endif

// ============== TEST INFO ==============

void runTest(const Test &test);
extern const Test TEST_A;
extern const Test TEST_B;
extern const Test TEST_C;
extern const Test TEST_D;
extern const Test TEST_E;
#include "tests.cpp"

const Test TEST_A = {
    "a",
    bestScoreA,
    SOLVER(testA::solveTest),
    -1
};

const Test TEST_B = {
    "b",
    bestScoreB,
    SOLVER(testB::solveTest),
    -1
};

const Test TEST_C = {
    "c",
    bestScoreC,
    SOLVER(testC::solveTest),
    -1
};

const Test TEST_D = {
    "d",
    bestScoreD,
    SOLVER(testD::solveTest),
    -1
};

const Test TEST_E = {
    "e",
    bestScoreE,
    SOLVER(testE::solveTest),
    -1
};

// =======================================

void runTest(const Test &test) {
    cerr << "running " << test.name << endl;
    currentTest = test;
    readInputFile(test.name);
    test.solve();
    int score = scoreResult();
    cerr << test.name << " score: " << score;
    if (score > test.bestScore) {
        cerr << ", IMPROVED by " << score - test.bestScore << " !!!!!!!!!!!!!" << endl;
    } else if (score < test.bestScore) {
        cerr << ", DECREASED by " << test.bestScore - score << endl;
    } else {
        cerr << ", OPTIMAL" << endl;
    }
    writeOutputFile(test.name);
    cerr << endl;
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        inputFolder = "input/";
    } else {
        inputFolder = argv[1];
        if (inputFolder.back() != '/' && inputFolder.back() != '\\') {
            inputFolder += '/';
        }
    }
    cerr << "reading inputs from " << inputFolder << endl;

    runTests();

    return 0;
}
