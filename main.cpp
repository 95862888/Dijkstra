#include <bits/stdc++.h>

#define pb push_back
#define F first
#define S second

using namespace std;

typedef unsigned long long int ulli;

vector<vector<pair<ulli, ulli>>> generateRandomGraph(int numOfVerteces, int numOfEdges, bool completeGraph) {
    vector<vector<ulli>> adjacencyMatrix(numOfVerteces, vector<ulli>(numOfVerteces, INT_MAX));

    if(numOfEdges > 0 || completeGraph) {
        for (int i = 0; i < numOfVerteces; ++i) {
            for (int j = i; j < numOfVerteces; ++j) {
                if (rand() % 2 || completeGraph) {
                    adjacencyMatrix[i][j] = abs(rand()) % 100;
                    numOfEdges--;
                } else {
                    adjacencyMatrix[i][j] = INT_MAX;
                }

                if (i == j)
                    adjacencyMatrix[i][j] = 0;

                if (numOfEdges <= 0 && !completeGraph)
                    break;
            }
            if (numOfEdges <= 0 && !completeGraph)
                break;
        }
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

void printAdjacencyList(vector<vector<pair<ulli, ulli>>>& g) {
    for (vector<pair<ulli, ulli>>& v : g) {
        for (pair<ulli, ulli>& nb : v)
            cout << nb.F << ' ';
        if(!v.empty())
            cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    srand(time (0));

    const int maxNumOfVerteces = 20;
    ofstream fout("D:/algo/base_case.txt");
    vector<vector<pair<ulli, ulli>>> g;
    ulli op;
    ulli maxOP;
    ulli minOP;
    for (int i = 2; i < 20; ++i) {
        maxOP = -1;
        minOP = ULONG_LONG_MAX;
        for (int j = 0; j < 1000; ++j) {
            op = 0;

            int numOfEdges = abs(rand()) % (((i * (i - 1)) / 2) + 1);
            g = generateRandomGraph(i, numOfEdges, false);
            minDistToEachVertex(op, g);

            if(op > maxOP)
                maxOP = op;
            if(op < minOP)
                minOP = op;
        }

        fout << minOP << ' ' << maxOP << '\n';
    }

    return 0;
}
