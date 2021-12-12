#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct node
{
    node(std::string label, bool small)
        : label(label), end(label == "end"), small(small), visited(false) {}

    std::string label;
    bool end, small, visited;
    std::vector<int> neighbours;
};

struct graph
{
    void add_edge(std::string a, std::string b);
    void add_node(std::string label);
    int dfs(int i, bool revisit_used = false);

    std::vector<node> nodes;
    std::map<std::string, int> indices;
    int start_i = 0;
};

int main(int argc, char *argv[])
{
    std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
    graph g;

    // Get input
    std::string line;
    int istart = 0;
    while (std::cin >> line)
    {
        std::stringstream ss(line);
        std::string a, b;
        getline(ss, a, '-');
        getline(ss, b);
        g.add_node(a);
        g.add_node(b);
        g.add_edge(a,b);
        g.add_edge(b,a);
    }

    std::cout << g.dfs(g.start_i) << std::endl;

    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Elapsed time: " << dt.count() << " seconds." << std::endl;

    return 0;
}

void graph::add_edge(std::string a, std::string b)
{
    if (a != "end" && b != "start")
        nodes[indices[a]].neighbours.push_back(indices[b]);
}

void graph::add_node(std::string label)
{
    static int i = 0;
    if (indices.count(label) == 0)
    {
        if (label == "start")
            start_i = i;
        indices[label] = i++;
        bool small = label[0] >= 'a' && label[0] <= 'z';
        node n(label, small);
        nodes.push_back(n);
    }
}

int graph::dfs(int i, bool revisit_used)
{
    node *n = &nodes[i];
    if (n->end)
        return 1;

    if (n->visited && n->small && revisit_used)
        return 0;

    bool used_now = false;
    if (n->visited && n->small && !revisit_used)
        revisit_used = used_now = true;

    int ret = 0;
    n->visited = true;
    for (int j : n->neighbours)
        ret += dfs(j, revisit_used);
    n->visited = used_now;
    return ret;
}
