#include "tree.hpp"

#include <chrono>
#include <iostream>
#include <sstream>

void print_tree(tree *t)
{
    // If this is a leaf node, print the data
    if (t->left == nullptr && t->right == nullptr)
        std::cout << (int)t->data;
    else
    {
        std::cout << "[";
        print_tree(t->left);
        std::cout << ",";
        print_tree(t->right);
        std::cout << "]";
    }
}

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();

    std::string line;
    std::cin >> line;
    std::stringstream ss(line);
    tree *t = new tree(ss);

    while (std::cin >> line)
    {
        ss.str(line);
        tree *l = t, *r = new tree(ss);
        t = new tree(l, r);
        t->reduce();
    }
    std::cout << t->magnitude<uint16_t>() << std::endl;

    delete t;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
