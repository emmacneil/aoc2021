#include <chrono>
#include <iostream>

bool turn(int &pos, int &score, int &n_rolls)
{
    static int d = 1;
    int m = 3*d + 3;
    d += 3; // This will make the dice roll higher than 1000, but it doesn't matter after we reduce modulo 10.
    n_rolls += 3;
    pos = (pos + m - 1) % 10 + 1;
    score += pos;
    return score < 1000;
}

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    int pos1, pos2, score1 = 0, score2 = 0, n_rolls = 0;
    std::cin.ignore(28); // Ignore "Player 1 starting position: "
    std::cin >> pos1;
    std::cin.ignore(28);
    std::cin >> pos2;

    while (turn(pos1, score1, n_rolls) && turn(pos2, score2, n_rolls))
        continue;

    std::cout << n_rolls*std::min(score1, score2) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
