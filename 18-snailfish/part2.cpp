#include "tree.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

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
    std::vector<std::string> lines;
    uint16_t max_mag = 0;

    while (std::cin >> line)
        lines.push_back(line);

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines.size(); j++)
        {
            if (i == j) continue;

            tree *t, *l, *r;
            std::stringstream ss;
            uint16_t mag;

            ss.str(lines[i]);
            l = str_to_tree(ss);
            ss.str(lines[j]);
            r = str_to_tree(ss);

            t = new tree;
            t->left = l;
            t->right = r;
            l->parent = t;
            r->parent = t;
            t->reduce();
            mag = t->magnitude();
            max_mag = mag > max_mag ? mag : max_mag;
            delete t;
        }
    }

    std::cout << max_mag << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}
