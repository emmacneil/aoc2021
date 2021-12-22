#include <chrono>
#include <iostream>
#include <stdint.h>

struct node
{
    node() : player1_wins(0), player2_wins(0) {}
    int64_t player1_wins, player2_wins;
};

struct state
{
    state() = default;
    state(int n) : player((n / 44100) % 2), pos1((n / 4410) % 10), pos2((n / 441) % 10 ), score1((n / 21) % 21), score2(n % 21) {}
    int to_int() const { return (((player * 10 + pos1) * 10 + pos2) * 21 + score1) * 21 + score2; }
    int player, pos1, pos2, score1, score2;
};

const int N_STATES = 2 * 10 * 10 * 21 * 21;
node nodes[N_STATES];

void precompute(int i);

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int pos1, pos2;
    std::cin.ignore(28); // Ignore "Player 1 starting position: "
    std::cin >> pos1;
    std::cin.ignore(28);
    std::cin >> pos2;

    state s;
    s.player = 0;
    s.pos1 = pos1;
    s.pos2 = pos2;
    s.score1 = 0;
    s.score2 = 0;

    int si = s.to_int();
    node* n = nodes + si;
    precompute(si);

    std::cout << std::max(n->player1_wins, n->player2_wins) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

void precompute(int i)
{
    const int n_rolls = 7;
    const int rolls[]       = { 3, 4, 5, 6, 7, 8, 9 };
    const int64_t chances[] = { 1, 3, 6, 7, 6, 3, 1 };

    node *n = nodes + i;
    if (n->player1_wins || n->player2_wins)
        return;

    const state curr(i);
    state next(i);
    if (curr.player == 0)
    {
        for (int j = 0; j < n_rolls; j++)
        {
            next.player = 1;
            next.pos1 = curr.pos1 + rolls[j];
            if (next.pos1 >= 10) next.pos1 -= 10;
            if (next.pos1 == 0)  next.score1 = curr.score1 + 10;
            else                 next.score1 = curr.score1 + next.pos1;
            if (next.score1 >= 21) n->player1_wins += chances[j];
            else
            {
                int k = next.to_int();
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
            next.player = 0;
            next.pos2 = curr.pos2 + rolls[j];
            if (next.pos2 >= 10) next.pos2 -= 10;
            if (next.pos2 == 0)  next.score2 = curr.score2 + 10;
            else                 next.score2 = curr.score2 + next.pos2;
            if (next.score2 >= 21) n->player2_wins += chances[j];
            else
            {
                int k = next.to_int();
                node* m = nodes + k;
                precompute(k);

                n->player1_wins += chances[j]*(m->player1_wins);
                n->player2_wins += chances[j]*(m->player2_wins);
            }
        }
    }
}
