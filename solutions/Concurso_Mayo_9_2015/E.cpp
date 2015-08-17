/*
2
8 12
1 3
3 2
2 1
1 4
4 5
5 6
6 4
4 7
8 4
8 7
6 8
6 7
8
1 2 3 4 5 6 7 8

3 4
1 2
2 1
1 3
2 3
3
1 2 3
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
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
	int to, weight;
    int backEdge, strong, type, visited; //optional
	Edge(int to, int weight = 1) : to(to), weight(weight), strong(0), visited(0) {}
};
struct Graph {
	int V; bool undirected;
	vector<vector<Edge> > edges;
	Graph(int v, bool undirected) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
	void connect(int from, Edge edge) {
		edges[from].pb(edge);
		if(undirected) {
			int aux = edge.to;
			edge.to = from;
			edges[aux].pb(edge);
            edges[from].back().backEdge = edges[aux].size() - 1; //optional
            edges[aux].back().backEdge = edges[from].size() - 1; //optional
		}
	}
};


vi low1, num1, components;
int counter1, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int cv) {
	low1[cv] = num1[cv] = counter1++;
	S.push(cv);
	visited[cv] = true;
	FORC(g.edges[cv], edge) {
		if(num1[edge->to] == -1)
			dfs(g, edge->to);
		if(visited[edge->to])
			low1[cv] = min(low1[cv], low1[edge->to]);        
	}
	if(low1[cv] == num1[cv]) {
		int index = SCCindex++;
		while(true) {
			int v = S.top(); S.pop(); visited[v] = 0;
			components[v] = index;
			if (cv == v)
				break;
		}
	}
}

vi stronglyConnectedComponents(Graph &g/*directed*/) {
	counter1 = 0, SCCindex = 0;
	visited = vector<bool>(g.V, 0);
	num1 = vi(g.V, -1), low1 = vi(g.V, 0), components = vi(g.V, 0);
	S = stack<int>();
	FOR(i, 0, g.V)
		if(num1[i] == -1)
			dfs(g, i);
	return components;
}

map<int, int> ans;

void dfs(Graph &g, int cv, vi &visited) {
	visited[cv] = 1;
	FORC(g.edges[cv], edge) {
		if (components[cv] != components[edge->to]) {
			ans[components[cv]]++;
		}
		if (!visited[edge->to]) {
			dfs(g, edge->to, visited);
		}
	}
}

mint main() {
	int TC;
	scanf("%lld", &TC);
	while(TC--) {
		ans.clear();
		int N, E;
		scanf("%lld %lld", &N, &E);
		Graph g(N, false);
		FOR(i, 0, E) {
			int from, to;
			scanf("%lld %lld", &from, &to);
			g.connect(from-1, Edge(to-1));
		}

		vi comps = stronglyConnectedComponents(g);
		vi visited(N, 0);
		FOR(i, 0, N) {
			if (!visited[i]) {
				dfs(g, i, visited);
			}
		}

		int Q;
		scanf("%lld", &Q);
		FOR(i, 0, Q) {
			int idx;
			scanf("%lld", &idx);
			printf("%lld\n", ans[components[idx-1]]);
		}

	}
}