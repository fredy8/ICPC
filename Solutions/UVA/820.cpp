/*
4
1 4 5
1 2 20
1 3 10
2 3 5
2 4 10
3 4 20
4
1 4 5
1 2 20
1 3 10
2 3 5
2 4 10
3 4 20
0
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
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef long long ll;

struct Edge {
    int weight;
    Edge(int weight = 1) : weight(weight) { }
};
struct Graph {
    int V;
    vector<vector<Edge> > edges;
    bool undirected;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) {
        edges.assign(V, vector<Edge>(V, Edge(0)));
    }
    void connect(int from, int to, int weight) {
        edges[from][to].weight += weight;
        if(undirected) edges[to][from].weight += weight;
    }
};

int augment(Graph &g, int flow, vi &parent, int source, int cv, int minEdge) {
	if(cv == source)
		return minEdge;
	if(parent[cv] != -1) {
		flow = augment(g, flow, parent, source, parent[cv], min(minEdge, g.edges[parent[cv]][cv].weight));
		g.edges[parent[cv]][cv].weight -= flow;
		g.edges[cv][parent[cv]].weight += flow;
	}
	return flow;
}

int maxFlow(Graph &g, int source, int sink) {
	int mf = 0, flow = -1;
	while(flow) {
		vi distanceTo(g.V, INF);
		distanceTo[source] = 0;
		queue<int> q; q.push(source);
		vi parent(g.V, -1);
		while(!q.empty()) {
			int currentVertex = q.front(); q.pop();
			if(currentVertex == sink) break;
			FOR(i, 0, g.V)
				if(g.edges[currentVertex][i].weight > 0 && distanceTo[i] == INF)
					distanceTo[i] = distanceTo[currentVertex] + 1, q.push(i), parent[i] = currentVertex;
		}
		mf += flow = augment(g, 0, parent, source, sink, INF);
	}
	return mf;
}

int main() {
	int N, tc = 1;
	while(cin >> N, N) {
		int S, T, E;
		cin >> S >> T >> E;
		S--, T--;
		Graph g(N);
		FOR(i, 0, E) {
			int from, to, cap;
			cin >> from >> to >> cap;
			g.connect(from-1, to-1, cap);
		}
		cout << "Network " << tc++ << endl << "The bandwidth is " << maxFlow(g, S, T) << "." << endl << endl;
	}
}