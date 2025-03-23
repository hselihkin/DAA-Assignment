#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
int clique = 0;
int counter[61];

unordered_set<int> setIntersection(const unordered_set<int> &a, const unordered_set<int> &b)
{
    unordered_set<int> res;
    for (int v : a)
    {
        if (b.count(v))
        {
            res.insert(v);
        }
    }
    return res;
}

void getIntersection(const unordered_set<int> &a, const unordered_set<int> &b, unordered_set<int> &res)
{
    res.clear();
    for (int v : a)
    {
        if (b.count(v))
        {
            res.insert(v);
        }
    }
}

void BronKerboschWithPivot(unordered_set<int> R, unordered_set<int> P, unordered_set<int> X, const vector<unordered_set<int>> &adj)
{
    // cout << R.size() << " " << P.size() << " " << X.size() << endl;

    if (P.empty() && X.empty())
    {
        cnt++;
        clique = max(clique, (int)R.size());
        int temp = (int)R.size();
        counter[temp]++;
        cout << "maximal clique: ";

        for (int v : R)
        {
            cout << v << " ";
        }
        cout << endl;
        cout << "Size: " << R.size() << endl;
        return;
    }

    vector<int> degen(P.begin(), P.end());
    sort(degen.begin(), degen.end(), [&](int u, int v)
         { return adj[u].size() < adj[v].size(); });

    // unordered_set<int> Pcopy = P;
    for (int v : degen)
    {
        unordered_set<int> newR = R;
        newR.insert(v);

        unordered_set<int> newP, newX;
        newP = setIntersection(P, adj[v]);
        newX = setIntersection(X, adj[v]);

        BronKerboschWithPivot(newR, newP, newX, adj);
        P.erase(v);
        X.insert(v);
    }
}

void BronKerbosch(unordered_set<int> &R, unordered_set<int> &P, unordered_set<int> &X, const vector<unordered_set<int>> &adj)
{
    // cout << R.size() << " " << P.size() << " " << X.size() << endl;

    if (P.empty() && X.empty())
    {
        cnt++;
        clique = max(clique, (int)R.size());
        cout << "maximal clique: ";

        for (int v : R)
        {
            cout << v << " ";
        }
        cout << endl;
        cout << "Size: " << R.size() << endl;
        return;
    }

    unordered_set<int> Pcopy = P;
    for (int v : Pcopy)
    {
        unordered_set<int> newR = R;
        newR.insert(v);

        unordered_set<int> newP, newX;
        newP = setIntersection(P, adj[v]);
        newX = setIntersection(X, adj[v]);

        BronKerbosch(newR, newP, newX, adj);
        P.erase(v);
        X.insert(v);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cout << "wrong number of arguments passed" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "Unable to open" << endl;
        return 1;
    }

    int N;
    cout << "Enter the number of nodes: ";
    cin >> N;

    vector<unordered_set<int>> adj(N);

    string line;
    while (getline(file, line))
    {

        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        stringstream ss(line);
        int fro, to;

        if (ss >> fro >> to)
        {
            adj[fro].insert(to);
            adj[to].insert(fro);
        }
    }
    file.close();

    // initialising R, P, X
    unordered_set<int> R, P, X;
    for (int i = 0; i < N; i++)
    {
        P.insert(i);
    }

    // cout << "\nBronKerbosch w/o Pivoting\n";
    // auto start_time = chrono::high_resolution_clock::now();
    // BronKerbosch(R, P, X, adj);
    // auto end_time = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();
    // cout << "Runtime for w/o Pivoting: " << duration << " seconds\n";
    // cout << "Number of Maximal Cliques: " << cnt << endl;
    // cout << "Largest Size of Clique: " << clique << endl;

    // cnt = 0;
    // clique = 0;

    // R.clear();
    // P.clear();
    // X.clear();
    // for (int i = 0; i < N; i++) {
    //     P.insert(i);
    // }

    cout << "\nBronKerbosch w/ Pivoting\n";
    auto start_time = chrono::high_resolution_clock::now();
    BronKerboschWithPivot(R, P, X, adj);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();
    cout << "Runtime for w/ Pivoting and Degeneracy Ordering: " << duration << " seconds\n";
    cout << "Number of Maximal Cliques: " << cnt << endl;
    cout << "Largest Size of Clique: " << clique << endl;

    for (int i = 0; i < 61; i++)
    {
        cout << "Clique Size " << i << ": " << counter[i] << "\n";
        ;
    }
    cout << endl;
}