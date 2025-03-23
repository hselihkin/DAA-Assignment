#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream infile("D:\\acad\\daa\\Wiki-Vote.txt");
    ofstream outfile("D:\\acad\\daa\\wiki_processed.txt");

    unordered_map<int, int> nodeMap;
    int curr = 0;
    vector<pair<int, int>> edges;

    string line;
    while (getline(infile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        stringstream ss(line);
        int fro, to;

        if (ss >> fro >> to)
        {
            if (nodeMap.find(fro) == nodeMap.end())
            {
                nodeMap[fro] = curr++;
            }
            if (nodeMap.find(to) == nodeMap.end())
            {
                nodeMap[to] = curr++;
            }

            int newFro = nodeMap[fro];
            int newTo = nodeMap[to];
            edges.emplace_back(newFro, newTo);
        }
    }

    infile.close();

    for (auto &edge : edges)
    {
        outfile << edge.first << "\t" << edge.second << "\n";
    }
    outfile.close();

    cout << "Reindexing done";
    return 0;
}