/*
5 4
1 2
2 3
1 3
1 5
0 0
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
    int to, weight;
    Edge(int to, int weight = 1) : to(to), weight(weight) {}
};
struct Graph {
    int V;
    vector<vector<Edge> > edges;
    int inDegree[110];
    bool undirected;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); memset(inDegree, 0, sizeof inDegree); }
    void connect(int from, Edge edge) {
        inDegree[edge.to]++;
        edges[from].push_back(edge);
        if(undirected) {
            int aux = edge.to;
            edge.to = from;
            edges[aux].push_back(edge);
        }
    }
};

vi topologicalSort(Graph &g) {
    vi order;
    int inDegree[g.V];
    FOR(i, 0, g.V) {
        inDegree[i] = g.inDegree[i];
        if(inDegree[i] == 0)
            order.push_back(i);
    }
    FOR(i, 0, order.size())
        FOR(j, 0, g.edges[order[i]].size())
            if(--inDegree[g.edges[order[i]][j].to] == 0)
                order.push_back(g.edges[order[i]][j].to);
    return order;
}

int main() {
    int N;
    while(cin >> N && N) {
        int E;
        cin >> E;

        Graph g(N, false);

        FOR(i, 0, E) {
            int from, to;
            cin >> from >> to;
            g.connect(from-1, Edge(to-1));
        }

        vi ts = topologicalSort(g);
        FORC(ts, it) {
            cout << *it+1 << " ";
        }
        cout << endl;
    }
}