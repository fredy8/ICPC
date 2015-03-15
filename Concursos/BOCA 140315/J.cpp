/*
4
km m mm cm
km = 1000 m
m = 100 cm
cm = 10 mm
4
m mm cm km
km = 100000 cm
km = 1000000 mm
m = 1000 mm
6
MiB Mib KiB Kib B b
B = 8 b
MiB = 1024 KiB
KiB = 1024 B
Mib = 1048576 b
Mib = 1024 Kib
6
Kib B MiB Mib KiB b
B = 8 b
MiB = 1048576 B
MiB = 1024 KiB
MiB = 8192 Kib
MiB = 8 Mib
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
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000000000
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

int arr[12][12];

mint main() {
	FOR(i, 0, 10)
		FOR(j, 0, 10)
			arr[i][j] = -1;

	int TC;
	cin >> TC;
	while(TC--) {
		int N;
		cin >> N;

		Graph g(N,)
	}
}
