#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#define MY_MACRO(i, j) { \
        int d = dist<i, j>(s.first); \
        if (d >= 0) \
        { \
            int cost = d * base_cost[s.first[i] - 'A']; \
            std::string new_state(s.first); \
            new_state[i] = s.first[j]; \
            new_state[j] = s.first[i]; \
            if (!S.count(new_state)) \
                Q.emplace(new_state, s.second + cost); \
        } \
    }

#define LOOP15(i) \
    MY_MACRO(i, 0) \
    MY_MACRO(i, 1) \
    MY_MACRO(i, 2) \
    MY_MACRO(i, 3) \
    MY_MACRO(i, 4) \
    MY_MACRO(i, 5) \
    MY_MACRO(i, 6) \
    MY_MACRO(i, 7) \
    MY_MACRO(i, 8) \
    MY_MACRO(i, 9) \
    MY_MACRO(i, 10) \
    MY_MACRO(i, 11) \
    MY_MACRO(i, 12) \
    MY_MACRO(i, 13) \
    MY_MACRO(i, 14)

#define LOOP225() \
    LOOP15(0) \
    LOOP15(1) \
    LOOP15(2) \
    LOOP15(3) \
    LOOP15(4) \
    LOOP15(5) \
    LOOP15(6) \
    LOOP15(7) \
    LOOP15(8) \
    LOOP15(9) \
    LOOP15(10) \
    LOOP15(11) \
    LOOP15(12) \
    LOOP15(13) \
    LOOP15(14)


typedef std::pair<std::string, int> state_t;
typedef std::priority_queue<state_t, std::vector<state_t>, std::function<bool(const state_t&, const state_t&)>> pqueue_t;

bool comp(const state_t& a, const state_t& b)
{
    return a.second > b.second;
}

template<size_t i, size_t j>
int dist(const std::string& state)
{
    return -1;
}

template<> int dist< 0, 7>(const std::string& state) { return (state[0] == 'A' && state[1] == '.' && state[8] == '.' && state[7] == '.') ? 4 : -1; }
template<> int dist< 0, 8>(const std::string& state) { return (state[0] == 'A' && state[1] == '.' && state[8] == '.') ? 3 : -1; }
template<> int dist< 0, 9>(const std::string& state) { return (state[0] == 'B' && state[1] == '.' && state[2] == '.' && state[10] == '.' && state[9] == '.') ? 6 : -1; }
template<> int dist< 0,10>(const std::string& state) { return (state[0] == 'B' && state[1] == '.' && state[2] == '.' && state[10] == '.') ? 5 : -1; }
template<> int dist< 0,11>(const std::string& state) { return (state[0] == 'C' && state[1] == '.' && state[2] == '.' && state[3] == '.' && state[12] == '.' && state[11] == '.') ? 8 : -1; }
template<> int dist< 0,12>(const std::string& state) { return (state[0] == 'C' && state[1] == '.' && state[2] == '.' && state[3] == '.' && state[12] == '.') ? 7 : -1; }
template<> int dist< 0,13>(const std::string& state) { return (state[0] == 'D' && state[1] == '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[14] == '.' && state[13] == '.') ? 10 : -1; }
template<> int dist< 0,14>(const std::string& state) { return (state[0] == 'D' && state[1] == '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[14] == '.') ? 9 : -1; }

template<> int dist< 1, 7>(const std::string& state) { return (state[1] == 'A' && state[8] == '.' && state[7] == '.') ? 3 : -1; }
template<> int dist< 1, 8>(const std::string& state) { return (state[1] == 'A' && state[8] == '.') ? 2 : -1; }
template<> int dist< 1, 9>(const std::string& state) { return (state[1] == 'B' && state[2] == '.' && state[10] == '.' && state[9] == '.') ? 5 : -1; }
template<> int dist< 1,10>(const std::string& state) { return (state[1] == 'B' && state[2] == '.' && state[10] == '.') ? 4 : -1; }
template<> int dist< 1,11>(const std::string& state) { return (state[1] == 'C' && state[2] == '.' && state[3] == '.' && state[12] == '.' && state[11] == '.') ? 7 : -1; }
template<> int dist< 1,12>(const std::string& state) { return (state[1] == 'C' && state[2] == '.' && state[3] == '.' && state[12] == '.') ? 6 : -1; }
template<> int dist< 1,13>(const std::string& state) { return (state[1] == 'D' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[14] == '.' && state[13] == '.') ? 9 : -1; }
template<> int dist< 1,14>(const std::string& state) { return (state[1] == 'D' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[14] == '.') ? 8 : -1; }

template<> int dist< 2, 7>(const std::string& state) { return (state[2] == 'A' && state[8] == '.' && state[7] == '.') ? 3 : -1; }
template<> int dist< 2, 8>(const std::string& state) { return (state[2] == 'A' && state[8] == '.') ? 2 : -1; }
template<> int dist< 2, 9>(const std::string& state) { return (state[2] == 'B' && state[10] == '.' && state[9] == '.') ? 3 : -1; }
template<> int dist< 2,10>(const std::string& state) { return (state[2] == 'B' && state[10] == '.') ? 2 : -1; }
template<> int dist< 2,11>(const std::string& state) { return (state[2] == 'C' && state[3] == '.' && state[12] == '.' && state[11] == '.') ? 5 : -1; }
template<> int dist< 2,12>(const std::string& state) { return (state[2] == 'C' && state[3] == '.' && state[12] == '.') ? 4 : -1; }
template<> int dist< 2,13>(const std::string& state) { return (state[2] == 'D' && state[3] == '.' && state[4] == '.' && state[14] == '.' && state[13] == '.') ? 6 : -1; }
template<> int dist< 2,14>(const std::string& state) { return (state[2] == 'D' && state[3] == '.' && state[4] == '.' && state[14] == '.') ? 5 : -1; }

template<> int dist< 3, 7>(const std::string& state) { return (state[3] == 'A' && state[2] == '.' && state[8] == '.' && state[7] == '.') ? 5 : -1; }
template<> int dist< 3, 8>(const std::string& state) { return (state[3] == 'A' && state[2] == '.' && state[8] == '.') ? 4 : -1; }
template<> int dist< 3, 9>(const std::string& state) { return (state[3] == 'B' && state[10] == '.' && state[9] == '.') ? 3 : -1; }
template<> int dist< 3,10>(const std::string& state) { return (state[3] == 'B' && state[10] == '.') ? 2 : -1; }
template<> int dist< 3,11>(const std::string& state) { return (state[3] == 'C' && state[12] == '.' && state[11] == '.') ? 3 : -1; }
template<> int dist< 3,12>(const std::string& state) { return (state[3] == 'C' && state[12] == '.') ? 2 : -1; }
template<> int dist< 3,13>(const std::string& state) { return (state[3] == 'D' && state[4] == '.' && state[14] == '.' && state[13] == '.') ? 5 : -1; }
template<> int dist< 3,14>(const std::string& state) { return (state[3] == 'D' && state[4] == '.' && state[14] == '.') ? 4 : -1; }

template<> int dist< 4, 7>(const std::string& state) { return (state[4] == 'A' && state[3] == '.' && state[2] == '.' && state[8] == '.' && state[7] == '.') ? 7 : -1; }
template<> int dist< 4, 8>(const std::string& state) { return (state[4] == 'A' && state[3] == '.' && state[2] == '.' && state[8] == '.') ? 6 : -1; }
template<> int dist< 4, 9>(const std::string& state) { return (state[4] == 'B' && state[3] == '.' && state[10] == '.' && state[9] == '.') ? 5 : -1; }
template<> int dist< 4,10>(const std::string& state) { return (state[4] == 'B' && state[3] == '.' && state[10] == '.') ? 4 : -1; }
template<> int dist< 4,11>(const std::string& state) { return (state[4] == 'C' && state[12] == '.' && state[11] == '.') ? 3 : -1; }
template<> int dist< 4,12>(const std::string& state) { return (state[4] == 'C' && state[12] == '.') ? 2 : -1; }
template<> int dist< 4,13>(const std::string& state) { return (state[4] == 'D' && state[14] == '.' && state[13] == '.') ? 3 : -1; }
template<> int dist< 4,14>(const std::string& state) { return (state[4] == 'D' && state[14] == '.') ? 2 : -1; }

template<> int dist< 5, 7>(const std::string& state) { return (state[5] == 'A' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[8] == '.' && state[7] == '.') ? 9 : -1; }
template<> int dist< 5, 8>(const std::string& state) { return (state[5] == 'A' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[8] == '.') ? 8 : -1; }
template<> int dist< 5, 9>(const std::string& state) { return (state[5] == 'B' && state[4] == '.' && state[3] == '.' && state[10] == '.' && state[9] == '.') ? 7 : -1; }
template<> int dist< 5,10>(const std::string& state) { return (state[5] == 'B' && state[4] == '.' && state[3] == '.' && state[10] == '.') ? 6 : -1; }
template<> int dist< 5,11>(const std::string& state) { return (state[5] == 'C' && state[4] == '.' && state[12] == '.' && state[11] == '.') ? 5 : -1; }
template<> int dist< 5,12>(const std::string& state) { return (state[5] == 'C' && state[4] == '.' && state[12] == '.') ? 4 : -1; }
template<> int dist< 5,13>(const std::string& state) { return (state[5] == 'D' && state[14] == '.' && state[13] == '.') ? 3 : -1; }
template<> int dist< 5,14>(const std::string& state) { return (state[5] == 'D' && state[14] == '.') ? 2 : -1; }

template<> int dist< 6, 7>(const std::string& state) { return (state[6] == 'A' && state[5] == '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[8] == '.' && state[7] == '.') ? 10 : -1; }
template<> int dist< 6, 8>(const std::string& state) { return (state[6] == 'A' && state[5] == '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[8] == '.') ? 9 : -1; }
template<> int dist< 6, 9>(const std::string& state) { return (state[6] == 'B' && state[5] == '.' && state[4] == '.' && state[3] == '.' && state[10] == '.' && state[9] == '.') ? 8 : -1; }
template<> int dist< 6,10>(const std::string& state) { return (state[6] == 'B' && state[5] == '.' && state[4] == '.' && state[3] == '.' && state[10] == '.') ? 7 : -1; }
template<> int dist< 6,11>(const std::string& state) { return (state[6] == 'C' && state[5] == '.' && state[4] == '.' && state[12] == '.' && state[11] == '.') ? 6 : -1; }
template<> int dist< 6,12>(const std::string& state) { return (state[6] == 'C' && state[5] == '.' && state[4] == '.' && state[12] == '.') ? 5 : -1; }
template<> int dist< 6,13>(const std::string& state) { return (state[6] == 'D' && state[5] == '.' && state[14] == '.' && state[13] == '.') ? 4 : -1; }
template<> int dist< 6,14>(const std::string& state) { return (state[6] == 'D' && state[5] == '.' && state[14] == '.') ? 3 : -1; }

template<> int dist< 7, 0>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[1] == '.' && state[0] == '.') ? 4 : -1; }
template<> int dist< 7, 1>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[1] == '.') ? 3 : -1; }
template<> int dist< 7, 2>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[2] == '.') ? 3 : -1; }
template<> int dist< 7, 3>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[2] == '.' && state[3] == '.') ? 5 : -1; }
template<> int dist< 7, 4>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[2] == '.' && state[3] == '.' && state[4] == '.') ? 7 : -1; }
template<> int dist< 7, 5>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.') ? 9 : -1; }
template<> int dist< 7, 6>(const std::string& state) { return (state[7] != 'A' && state[7] != '.' && state[8] == '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 10 : -1; }

template<> int dist< 8, 0>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[1] == '.' && state[0] == '.') ? 3 : -1; }
template<> int dist< 8, 1>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[1] == '.') ? 2 : -1; }
template<> int dist< 8, 2>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[2] == '.') ? 2 : -1; }
template<> int dist< 8, 3>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[2] == '.' && state[3] == '.') ? 4 : -1; }
template<> int dist< 8, 4>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[2] == '.' && state[3] == '.' && state[4] == '.') ? 6 : -1; }
template<> int dist< 8, 5>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.') ? 8 : -1; }
template<> int dist< 8, 6>(const std::string& state) { return ((state[7] != 'A' || state[8] != 'A') && state[8] != '.' && state[2] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 9 : -1; }

template<> int dist< 9, 0>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 6 : -1; }
template<> int dist< 9, 1>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[2] == '.' && state[1] == '.') ? 5 : -1; }
template<> int dist< 9, 2>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[2] == '.') ? 3 : -1; }
template<> int dist< 9, 3>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[3] == '.') ? 3 : -1; }
template<> int dist< 9, 4>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[3] == '.' && state[4] == '.') ? 5 : -1; }
template<> int dist< 9, 5>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.') ? 7 : -1; }
template<> int dist< 9, 6>(const std::string& state) { return (state[9] != 'B' && state[9] != '.' && state[10] == '.' && state[3] == '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 8 : -1; }

template<> int dist<10, 0>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 5 : -1; }
template<> int dist<10, 1>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[2] == '.' && state[1] == '.') ? 4 : -1; }
template<> int dist<10, 2>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[2] == '.') ? 2 : -1; }
template<> int dist<10, 3>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[3] == '.') ? 2 : -1; }
template<> int dist<10, 4>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[3] == '.' && state[4] == '.') ? 4 : -1; }
template<> int dist<10, 5>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[3] == '.' && state[4] == '.' && state[5] == '.') ? 6 : -1; }
template<> int dist<10, 6>(const std::string& state) { return ((state[9] != 'B' || state[10] != 'B') && state[10] != '.' && state[3] == '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 7 : -1; }

template<> int dist<11, 0>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 8 : -1; }
template<> int dist<11, 1>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.') ? 7 : -1; }
template<> int dist<11, 2>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[3] == '.' && state[2] == '.') ? 5 : -1; }
template<> int dist<11, 3>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[3] == '.') ? 3 : -1; }
template<> int dist<11, 4>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[4] == '.') ? 3 : -1; }
template<> int dist<11, 5>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[4] == '.' && state[5] == '.') ? 5 : -1; }
template<> int dist<11, 6>(const std::string& state) { return (state[11] != 'C' && state[11] != '.' && state[12] == '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 6 : -1; }

template<> int dist<12, 0>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[3] == '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 7 : -1; }
template<> int dist<12, 1>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[3] == '.' && state[2] == '.' && state[1] == '.') ? 6 : -1; }
template<> int dist<12, 2>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[3] == '.' && state[2] == '.') ? 4 : -1; }
template<> int dist<12, 3>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[3] == '.') ? 2 : -1; }
template<> int dist<12, 4>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[4] == '.') ? 2 : -1; }
template<> int dist<12, 5>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[4] == '.' && state[5] == '.') ? 4 : -1; }
template<> int dist<12, 6>(const std::string& state) { return ((state[11] != 'C' || state[12] != 'C') && state[12] != '.' && state[4] == '.' && state[5] == '.' && state[6] == '.') ? 5 : -1; }

template<> int dist<13, 0>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 10 : -1; }
template<> int dist<13, 1>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.') ? 9 : -1; }
template<> int dist<13, 2>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[4] == '.' && state[3] == '.' && state[2] == '.') ? 7 : -1; }
template<> int dist<13, 3>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[4] == '.' && state[3] == '.') ? 5 : -1; }
template<> int dist<13, 4>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[4] == '.') ? 3 : -1; }
template<> int dist<13, 5>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[5] == '.') ? 3 : -1; }
template<> int dist<13, 6>(const std::string& state) { return (state[13] != 'D' && state[13] != '.' && state[14] == '.' && state[5] == '.' && state[6] == '.') ? 4 : -1; }

template<> int dist<14, 0>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.' && state[0] == '.') ? 9 : -1; }
template<> int dist<14, 1>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[4] == '.' && state[3] == '.' && state[2] == '.' && state[1] == '.') ? 8 : -1; }
template<> int dist<14, 2>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[4] == '.' && state[3] == '.' && state[2] == '.') ? 6 : -1; }
template<> int dist<14, 3>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[4] == '.' && state[3] == '.') ? 4 : -1; }
template<> int dist<14, 4>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[4] == '.') ? 2 : -1; }
template<> int dist<14, 5>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[5] == '.') ? 2 : -1; }
template<> int dist<14, 6>(const std::string& state) { return ((state[13] != 'D' || state[14] != 'D') && state[14] != '.' && state[5] == '.' && state[6] == '.') ? 3 : -1; }

int main(int argc, char* argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line, start_state = "...............";

    getline(std::cin, line);
    getline(std::cin, line);
    getline(std::cin, line);
    start_state[8] = line[3];
    start_state[10] = line[5];
    start_state[12] = line[7];
    start_state[14] = line[9];
    getline(std::cin, line);
    start_state[7] = line[3];
    start_state[9] = line[5];
    start_state[11] = line[7];
    start_state[13] = line[9];

    pqueue_t Q{ comp };
    std::unordered_set<std::string> S;
    Q.emplace(start_state, 0);
    int base_cost[4] = { 1, 10, 100, 1000 };

    while (Q.top().first != ".......AABBCCDD")
    {
        state_t s = Q.top();
        Q.pop();
        //if (s.second % 100 == 0)
        //    std::cout << s.first << " (" << s.second << ") [" << Q.size() << "]" << std::endl;

        // If we haven't been to this state before
        if (!S.count(s.first))
        {
            LOOP225()
                ;
        }
        S.insert(s.first);
    }
    //std::cout << Q.top().first << std::endl;
    std::cout << Q.top().second << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}