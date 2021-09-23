#include <bits/stdc++.h>

#define pb push_back
#define F first
#define S second

using namespace std;

typedef unsigned long long int ulli;

vector<vector<pair<ulli, ulli>>> generateRandomGraph(int numOfVerteces, int numOfEdges, bool completeGraph) {
    vector<vector<ulli>> adjacencyMatrix(numOfVerteces, vector<ulli>(numOfVerteces));
    for (int i = 0; i < numOfVerteces; ++i) {
        for (int j = i; j < numOfVerteces; ++j) {
            if(rand() % 2 || completeGraph) {
                adjacencyMatrix[i][j] = abs(rand()) % 100;
                numOfEdges--;
            }
            else {
                adjacencyMatrix[i][j] = INT_MAX;
            }

            if(i == j)
                adjacencyMatrix[i][j] = 0;

            if(numOfEdges == 0 && !completeGraph)
                break;
        }
        if(numOfEdges == 0 && !completeGraph)
            break;
    }

    vector<vector<pair<ulli, ulli>>> adjacencyList(numOfVerteces);
    for (int i = 0; i < numOfVerteces; ++i) {
        for (int j = i; j < numOfVerteces; ++j) {
            if(adjacencyMatrix[i][j] != INT_MAX)
                adjacencyList[i].pb({j, adjacencyMatrix[i][j]});
        }
    }

    return adjacencyList;
};

//aka Dijkstra
vector<ulli> minDistToEachVertex(ulli& op, vector<vector<pair<ulli, ulli>>>& g) {
    vector<ulli> minDist(g.size(), ULLONG_MAX); //array of minimum distances to each vertex

    minDist[0] = 0; op++;

    set<pair<ulli, ulli>> q;
    q.insert({minDist[0], 0}); //pair<distance, vertex>
    if(!q.empty()) op += log2l(q.size());
    while(!q.empty()) {
        int vertex = q.begin()->second; op++;
        q.erase(q.begin()); if(!q.empty()) op += log2l(q.size());

        //iterate over all adjacent vertices
        for (size_t j = 0; j < g[vertex].size(); ++j, op += 2) {
            ulli to = g[vertex][j].first; op++;
            ulli distance = g[vertex][j].second; op++;

            op += 2;
            if (minDist[vertex] + distance < minDist[to]) {
                q.erase({minDist[to], to}); if(!q.empty()) op += log2l(q.size());
                minDist[to] = minDist[vertex] + distance; op += 2;
                q.insert({minDist[to], to}); if(!q.empty()) op += log2l(q.size());
            }
        }
    }

    return minDist;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n = 20;

    ofstream fout_base_case("D:\\algo\\base_case.txt");
    ulli op;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= (i * (i - 1)) / 2; ++j) {
            op = 0;

            vector<vector<pair<ulli, ulli>>> g = generateRandomGraph(i, j, false); //adjacencyList
            minDistToEachVertex(op, g);
            fout_base_case << i << ' '  << j << ' ' << op << '\n';
        }
    }
    fout_base_case.close();

    ofstream fout_worst_case("D:\\algo\\worst_case.txt");
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= (i * (i - 1)) / 2; ++j) {
            op = 0;

            //generate the complete graphs(every pair of distinct vertices is connected by a unique edge)
            //worst case
            vector<vector<pair<ulli, ulli>>> g = generateRandomGraph(i, j, true);
            minDistToEachVertex(op, g);
            fout_worst_case << i << ' '  << j << ' ' << op << '\n';
        }
    }
    fout_worst_case.close();

    ofstream fout_best_case("D:\\algo\\best_case.txt");
    for (int i = 2; i <= n; ++i) {
        op = 0;

        //xd graph without edges
        vector<vector<pair<ulli, ulli>>> g = generateRandomGraph(i, 0, false);
        minDistToEachVertex(op, g);
        fout_best_case << i << ' '  << 0 << ' ' << op << '\n';
    }
    fout_best_case.close();

    return 0;
}