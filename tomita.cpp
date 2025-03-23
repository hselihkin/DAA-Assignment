#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

unordered_map<int, unordered_set<int>> graph;
vector<int> clique_size_distr(100);
int num_max_cliques = 0;
auto start = high_resolution_clock::now();

void expand(set<int> &Q, set<int> &SUBG, set<int> &CAND, set<int> &FINI)
{
    if (SUBG.empty())
    {
        num_max_cliques++;
        clique_size_distr[Q.size()]++;
    }
    else
    {
        // choosing pivot
        int pivot = -1;
        int max_inter = -1;
        for (auto node : SUBG)
        {
            int inter = 0;
            for (auto adj : graph[node])
            {
                if (CAND.find(adj) != CAND.end())
                {
                    inter++;
                }
            }
            if (inter > max_inter)
            {
                max_inter = inter;
                pivot = node;
            }
        }

        // candidate set
        vector<int> candidates;
        for (auto node : CAND)
        {
            if (graph[pivot].find(node) == graph[pivot].end())
            {
                candidates.push_back(node);
            }
        }

        // recursion
        for (auto node : candidates)
        {
            set<int> SUBG_q, CAND_q;
            for (auto v : SUBG)
            {
                if (graph[node].find(v) != graph[node].end())
                {
                    SUBG_q.insert(v);
                }
            }
            for (auto v : CAND)
            {
                if (graph[node].find(v) != graph[node].end())
                {
                    CAND_q.insert(v);
                }
            }

            Q.insert(node);
            expand(Q, SUBG_q, CAND_q, FINI);
            Q.erase(node);

            CAND.erase(node);
            FINI.insert(node);
        }
    }
}

int main(int argc, char *argv[])
{
    // taking file name input from terminal
    if (argc != 2)
    {
        cout << "Incorrect number of arguments passed" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    int u, v;
    string line;

    // Ignore comments and empty lines
    while (getline(infile, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        istringstream iss(line);
        if (iss >> u >> v)
        {
            graph[u].insert(v);
            graph[v].insert(u);
        }
    }

    // directed graph
    // int u, v;
    // while (infile >> u >> v)
    // {
    //     graph[u].insert(v);
    //     graph[v].insert(u);
    // }

    set<int> Q;    // current clique
    set<int> SUBG; // set of nodes that can be added to cliques
    set<int> CAND; // nodes from SUBG that havent been seen
    set<int> FINI; //  finished nodes

    // initialization
    for (auto node : graph)
    {
        SUBG.insert(node.first);
        CAND.insert(node.first);
    }

    // algorithm
    expand(Q, SUBG, CAND, FINI);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    // displaying results
    int max_clique_size = 0;
    cout << "Time taken: " << duration.count() << " seconds" << endl;
    cout << "number of max cliques: " << num_max_cliques << endl;
    for (int size = 0; size < clique_size_distr.size(); size++)
    {
        if (clique_size_distr[size] == 0)
        {
            continue;
        }

        cout << "number of " << size << " size cliques: " << clique_size_distr[size] << endl;

        if (size > max_clique_size)
        {
            max_clique_size = size;
        }
    }
    cout << "Largest Cliques Size: " << max_clique_size << endl;
    cout << endl;

    return 0;
}