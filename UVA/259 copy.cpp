/*
A4 01234;
Q1 5;
P4 56789;

A4 01234;
Q1 5;
P5 56789;
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
    int V; bool undirected;
    vector<vector<Edge> > edges;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) {
        edges.assign(V, vector<Edge>(V, Edge(0)));
    }
    void connect(int from, int to, int weight = 1) {
        edges[from][to].weight = weight;
        if(undirected) edges[to][from].weight = weight;
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

//O(V^3*E)
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
	string line;
	while(getline(cin, line)) {
		Graph g(38, false);
		bool end = false;
		int expectedFlow = 0;
		while(!end && line.length()) {
			expectedFlow += line[1] - '0';
			g.connect(0, 1 + line[0] - 'A', line[1] - '0');
			FOR(i, 3, line.length()-1)
				g.connect(1 + line[0] - 'A', 1 + 26 + line[i] - '0');
			end = !getline(cin, line);
		}
		FOR(i, 27, 37)
			g.connect(i, 37, 1);
		int mf = maxFlow(g, 0, 37);
		if(mf != expectedFlow)
			cout << "!" << endl;
		else {
			char comps[10] = {0};
			FOR(i, 1, 27) {
				FOR(j, 27, 37) {
					if(g.edges[j][i].weight) {
						comps[j-27] = i-1+'A';
					}
				}
			}
			FOR(i, 0, 10)
				cout << (comps[i] ? comps[i] : '_');
			cout << endl;
		}
	}
}