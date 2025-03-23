#include <bits/stdc++.h>
using namespace std;

vector<unordered_set<int>> adjList;
vector<int> degree;
vector<int> vertexOrder;
unordered_map<int, int> oldToNew;

// helper arrays
vector<int> T;
unordered_map<int, int> S;
int cliqueCount = 0; // result

// Read graph from file, skip the #s in the first few lines.
void readGraph(const string &filename) {
    ifstream infile(filename);
    int u, v;
    unordered_map<int, int> vertexMap;
    int index = 0;
    string line;
    vector<pair<int, int>> edges;

    while (getline(infile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        istringstream iss(line);
        if (iss >> u >> v) { // Read integers from the line
            if (vertexMap.find(u) == vertexMap.end()) vertexMap[u] = index++;
            if (vertexMap.find(v) == vertexMap.end()) vertexMap[v] = index++;
            edges.push_back({vertexMap[u], vertexMap[v]});
        }
    }

    int n = index;
    adjList.resize(n);
    degree.resize(n, 0);
    vertexOrder.resize(n);
    T.resize(n, 0);

    for (auto &[u, v] : edges) {
        adjList[u].insert(v);
        adjList[v].insert(u);
        degree[u]++;
        degree[v]++;
    }

    for (auto &[oldId, newId] : vertexMap) {
        oldToNew[oldId] = newId;
    }
}

// Sort vertices by degree using bucket sort
void sortVerticesByDegree(int n) {
    vector<vector<int>> bucket(n);
    for (int i = 0; i < n; i++) {
        bucket[degree[i]].push_back(i);
    }
    int index = 0;
    for (int d = 0; d < n; d++) {
        for (int v : bucket[d]) {
            vertexOrder[index++] = v;
        }
    }
}

// Initialize S and T for clique finding
void initializeSandT(int n) {
    fill(T.begin(), T.end(), 0);
    S.clear();
}

// Original maximality test - ensures correctness
bool maximalityTest(const unordered_set<int>& C) {
    for (int y = 0; y < adjList.size(); y++) {
        if (C.find(y) == C.end()) { // y is outside clique
            bool fullyConnected = true;
            for (int x : C) {
                if (adjList[y].find(x) == adjList[y].end()) { // y is missing a connection
                    fullyConnected = false;
                    break;
                }
            }
            if (fullyConnected) return false; // Fails maximality test
        }
    }
    return true; // Passes maximality test
}

// Recursive function to expand and count maximal cliques
void UPDATE(unordered_set<int>& C, unordered_set<int>& candidates) {
    if (candidates.empty()) {
        if (maximalityTest(C)) { // Only count if truly maximal
            if(cliqueCount % 5000 == 0){
                printf("progress is happening, current count: %d\n", cliqueCount);
            }
            cliqueCount++;
        }
        return;
    }

    // Create a copy of candidates to iterate over, since we'll be modifying the original
    vector<int> candidatesCopy(candidates.begin(), candidates.end());
    
    for (int v : candidatesCopy) {
        candidates.erase(v);

        // Add v to clique
        C.insert(v);

        // Create new candidates set for next recursive call
        unordered_set<int> newCandidates;
        for (int u : candidates) {
            if (adjList[v].find(u) != adjList[v].end()) {
                newCandidates.insert(u);
            }
        }

        UPDATE(C, newCandidates);
        
        // Remove v from clique (backtracking)
        C.erase(v);
    }
}

// Start the clique finding process
void findCliques() {
    unordered_set<int> C;
    unordered_set<int> candidates;
    for (int v = 0; v < adjList.size(); v++) {
        candidates.insert(v);
    }
    cliqueCount = 0;
    UPDATE(C, candidates);
    cout << "Total Maximal Cliques Found: " << cliqueCount << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Command line usage error." << endl;
        return 1;
    }
    
    string filename = argv[1];
    readGraph(filename);

    int n = adjList.size();
    sortVerticesByDegree(n);
    initializeSandT(n);

    // Start timing
    auto start_time = chrono::high_resolution_clock::now();
    
    findCliques();
    
    // End timing
    auto end_time = chrono::high_resolution_clock::now();
    
    // Calculate duration in seconds
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();
    
    cout << "Time taken by findCliques(): " << duration << " seconds" << endl;
    return 0;
}