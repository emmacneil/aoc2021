#include <chrono>
#include <iostream>
#include <stdint.h>

const uint32_t PLAYER_1 = 0;
const uint32_t PLAYER_2 = 1;
const uint32_t N_STATES = 2 * 10 * 10 * 21 * 21;

struct node
{
    node() : player1_wins(0), player2_wins(0), visited(false) {}
    uint64_t player1_wins, player2_wins;
    bool visited;
};
node nodes[N_STATES];

struct state
{
    state() = default;
    state(uint32_t n)
    {
        score2 = n % 21; n /= 21;
        score1 = n % 21; n /= 21;
        pos2   = n % 10; n /= 10;
        pos1   = n % 10; n /= 10;
        player = n % 2;
    }
    uint32_t to_uint32() const { return (((player * 10 + pos1) * 10 + pos2) * 21 + score1) * 21 + score2; }
    uint32_t player, pos1, pos2, score1, score2;
    friend std::ostream& operator<<(std::ostream& os, const state& s)
    {
        return os << "{State: " << s.to_uint32()
                  << ", player = " << (s.player == PLAYER_1 ? 1 : 2)
                  << ", pos1 = " << s.pos1
                  << ", pos2 = " << s.pos2
                  << ", score1 = " << s.score1
                  << ", score2 = " << s.score2 << "}";
    }
};

void precompute(uint32_t i = 0);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    size_t pos1, pos2;
    std::cin.ignore(28); // Ignore "Player 1 starting position: "
    std::cin >> pos1;
    std::cin.ignore(28);
    std::cin >> pos2;

    state s;
    s.player = PLAYER_1;
    s.pos1 = pos1;
    s.pos2 = pos2;
    s.score1 = 0;
    s.score2 = 0;

    precompute(s.to_uint32());

    node* n = nodes + s.to_uint32();
    //std::cout << "Player 1 wins " << n->player1_wins << " times" << std::endl;
    //std::cout << "Player 2 wins " << n->player2_wins << " times" << std::endl;
    std::cout << std::max(n->player1_wins, n->player2_wins) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

void precompute(uint32_t i)
{
    const int n_rolls = 7;
    const int rolls[]        = { 3, 4, 5, 6, 7, 8, 9 };
    const uint64_t chances[] = { 1, 3, 6, 7, 6, 3, 1 };

    node *n = nodes + i;
    if (n->visited)
        return;
    n->visited = true;

    const state curr(i);
    state next(i);
    if (curr.player == PLAYER_1)
    {
        for (int j = 0; j < n_rolls; j++)
        {
            next.player = PLAYER_2;
            next.pos1 = curr.pos1 + rolls[j];
            if (next.pos1 >= 10) next.pos1 -= 10;
            if (next.pos1 == 0)  next.score1 = curr.score1 + 10;
            else                 next.score1 = curr.score1 + next.pos1;
            if (next.score1 >= 21) n->player1_wins += chances[j];
            else
            {
                uint32_t k = next.to_uint32();
                node* m = nodes + k;
                precompute(k);

                n->player1_wins += chances[j]*(m->player1_wins);
                n->player2_wins += chances[j]*(m->player2_wins);
            }
        }
    }
    else
    {
        for (int j = 0; j < n_rolls; j++)
        {
            next.player = PLAYER_1;
            next.pos2 = curr.pos2 + rolls[j];
            if (next.pos2 >= 10) next.pos2 -= 10;
            if (next.pos2 == 0)  next.score2 = curr.score2 + 10;
            else                 next.score2 = curr.score2 + next.pos2;
            if (next.score2 >= 21) n->player2_wins += chances[j];
            else
            {
                uint32_t k = next.to_uint32();
                node* m = nodes + k;
                precompute(k);

                n->player1_wins += chances[j]*(m->player1_wins);
                n->player2_wins += chances[j]*(m->player2_wins);
            }
        }
    }
}
