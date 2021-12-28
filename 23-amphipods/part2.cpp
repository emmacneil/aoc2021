#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

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

int check_path(const std::string& state, int i, int j)
{
    static int next[23][23] =
    {//   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 0, 1, 2, 2, 2, 2, 2,10,10,10,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        { 1, 1, 2, 3, 3, 3, 3,10,10,10,10,14,14,14,14, 3, 3, 3, 3, 3, 3, 3, 3},
        { 2, 2, 2, 3, 4, 4, 4, 2, 2, 2, 2,14,14,14,14,18,18,18,18, 4, 4, 4, 4},
        { 3, 3, 3, 3, 4, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3,18,18,18,18,22,22,22,22},
        { 4, 4, 4, 4, 4, 5, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,22,22,22,22},
        { 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        { 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
        { 9, 9, 9, 9, 9, 9, 9, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {10,10,10,10,10,10,10, 8, 8, 9,10,10,10,10,10,10,10,10,10,10,10,10,10},
        { 1, 1, 2, 2, 2, 2, 2, 9, 9, 9,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {12,12,12,12,12,12,12,12,12,12,12,11,12,12,12,12,12,12,12,12,12,12,12},
        {13,13,13,13,13,13,13,13,13,13,13,11,12,13,13,13,13,13,13,13,13,13,13},
        {14,14,14,14,14,14,14,14,14,14,14,12,12,13,14,14,14,14,14,14,14,14,14},
        { 2, 2, 2, 3, 3, 3, 3, 2, 2, 2, 2,13,13,13,14, 3, 3, 3, 3, 3, 3, 3, 3},
        {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,16,16,16,16,16,16,16},
        {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,16,17,17,17,17,17,17},
        {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,16,16,17,18,18,18,18,18},
        { 3, 3, 3, 3, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3,17,17,17,18, 4, 4, 4, 4},
        {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,19,20,20,20},
        {21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,19,20,21,21},
        {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,20,20,21,22},
        { 4, 4, 4, 4, 4, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,21,21,21,22}
    };
    static int cost[23][23] =
    {//  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,2,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0},
        {0,0,2,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0},
        {0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2},
        {0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,2,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
        {0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}
    };

    if (i == j) return 0;
    int next_i = next[i][j];
    if (state[next_i] != '.') return -100;
    return cost[i][next_i] + check_path(state, next_i, j);
}

int dist(const std::string& state, int i, int j)
{
    char src = state[i], dst = state[j];

    // If there is no amphipod at source position
    // Or if there is an amphipod at the destination
    if (src == '.' || dst != '.') return -1;

    // If we are moving an amphipod from hall to hall or from room to room
    if (i <= 6 && j <= 6) return -1;
    if (i >= 7 && j >= 7) return -1;

    // If we are trying to move an amphipod into the wrong room
    if (7  <= j && j <= 10 && src != 'A') return -1;
    if (11 <= j && j <= 14 && src != 'B') return -1;
    if (15 <= j && j <= 18 && src != 'C') return -1;
    if (19 <= j && j <= 22 && src != 'D') return -1;

    return check_path(state, i, j);
}

int main(int argc, char* argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line, start_state = "........DD..BC..AB..CA.";

    getline(std::cin, line);
    getline(std::cin, line);
    getline(std::cin, line);
    start_state[10] = line[3];
    start_state[14] = line[5];
    start_state[18] = line[7];
    start_state[22] = line[9];
    getline(std::cin, line);
    start_state[7] = line[3];
    start_state[11] = line[5];
    start_state[15] = line[7];
    start_state[19] = line[9];

    pqueue_t Q{ comp };
    std::unordered_set<std::string> S;
    Q.emplace(start_state, 0);
    int base_cost[4] = { 1, 10, 100, 1000 };

    int test_count = 0;
    while (Q.top().first != ".......AAAABBBBCCCCDDDD")
    {
        state_t s = Q.top();
        Q.pop();
        if (++test_count % 10000 == 0)
            std::cout << s.first << " (" << s.second << ") (" << Q.size() << ")" << std::endl;

        // If we haven't been to this state before
        if (!S.count(s.first))
        {
            for (int i = 0; i < 23; i++)
            {
                for (int j = 0; j < 23; j++)
                {
                    int d = dist(s.first, i, j);
                    // If amphipod at position i can move to j
                    if (d > 0)
                    {
                        // Add state
                        std::string new_state(s.first);
                        new_state[i] = s.first[j];
                        new_state[j] = s.first[i];
                        Q.emplace(new_state, s.second + d * base_cost[s.first[i] - 'A']);
                    }
                }
            }
        }
        S.insert(s.first);
    }
    std::cout << Q.top().second << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}