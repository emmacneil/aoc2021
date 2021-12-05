#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class bingo_board
{
public:
    int play(std::vector<int> &numbers);
    void reset();
    int score();
    friend std::istream& operator>>(std::istream &is, bingo_board &b);
private:
    int numbers[25];
    bool marked[25];
    int last_marked;

    bool bingo();
    bool mark(int n);
};

bool bingo_board::bingo()
{
    // The world needs a villain
    return (marked[ 0] && marked[ 1] && marked[ 2] && marked[ 3] && marked[ 4])
        || (marked[ 5] && marked[ 6] && marked[ 7] && marked[ 8] && marked[ 9])
        || (marked[10] && marked[11] && marked[12] && marked[13] && marked[14])
        || (marked[15] && marked[16] && marked[17] && marked[18] && marked[19])
        || (marked[20] && marked[21] && marked[22] && marked[23] && marked[24])
        || (marked[ 0] && marked[ 5] && marked[10] && marked[15] && marked[20])
        || (marked[ 1] && marked[ 6] && marked[11] && marked[16] && marked[21])
        || (marked[ 2] && marked[ 7] && marked[12] && marked[17] && marked[22])
        || (marked[ 3] && marked[ 8] && marked[13] && marked[18] && marked[23])
        || (marked[ 4] && marked[ 9] && marked[14] && marked[19] && marked[24]);
//        || (marked[ 0] && marked[ 6] && marked[12] && marked[18] && marked[24])
//        || (marked[ 4] && marked[ 8] && marked[12] && marked[16] && marked[20]);
}

bool bingo_board::mark(int n)
{
    for (int i = 0; i < 25; i++)
    {
        if (numbers[i] == n)
        {
            marked[i] = true;
            last_marked = n;
            return true;
        }
    }
    return false;
}

int bingo_board::play(std::vector<int> &numbers)
{
    int turns = 0;
    for (int n : numbers)
    {
        turns++;
        if (mark(n) && bingo())
        {
            break;
        }
    }
    return turns;
}

void bingo_board::reset()
{
    for (int i = 0; i < 25; i++)
        marked[i] = false;
}

int bingo_board::score()
{
    int ret = 0;
    for (int i = 0; i < 25; i++)
        ret += marked[i] ? 0 : numbers[i];
    ret *= last_marked;
    return ret;
}

std::istream& operator>>(std::istream &is, bingo_board &b)
{
    for (int i = 0; i < 25; i++)
    {
        is >> b.numbers[i];
    }
    return is;
}

int main (int argc, char *argv[])
{
    // Get the first line of comma-separated integers, and store the integers in a vector
    std::string line, tmp;
    std::vector<int> numbers;
    std::cin >> line;
    std::stringstream ss(line);
    while (getline(ss, tmp, ','))
        numbers.push_back(atoi(tmp.c_str()));

    // For each bingo game, determine on which turn it will win and its point score.
    // Keep track of the board that wins first.
    bingo_board board;
    unsigned int least_turns = 0xffffffff;
    int best_score = 0;
    while (std::cin >> board)
    {
        board.reset();
        int turns = board.play(numbers);
        int score = board.score();

        if (turns < least_turns)
        {
            least_turns = turns;
            best_score = score;
        }
    }

    std::cout << best_score << std::endl;

    return 0;
}
