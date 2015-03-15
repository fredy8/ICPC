/*
3 0
1 2 2
1 2 2
4 2
1 2 2
1 3 1
3 4 2
2 4
6 2
1 2 2
2 4 2
1 3 3
3 6 3
3 5 1
5 2
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std;
typedef long long ll; typedef pair<int, int> ii;
typedef vector<int> vi; typedef vector<ii> vii;
typedef vector<vi> vvi;

#define MAX 100000

struct Edge {
	int to, weight, useless;
	Edge(int to, int weight = 1) : to(to), weight(weight), useless(0) {}
};

struct Graph {
	int V;
	bool undirected;
	vector<vector<Edge> > edges;
	Graph(int v, bool undirected) : V(v), undirected(undirected) {
		edges.assign(V, vector<Edge>());
	}
	void connect(int from, Edge edge) {
		edges[from].pb(edge);
		if (undirected) {
			int aux = edge.to;
			edge.to = from;
			edges[aux].pb(edge);
		}
	}
};

int isFriend[MAX];
int parent[MAX];

bool containsFriend(Graph &g, int cv) {
	bool childContainsFriend = false;
	FORC(g.edges[cv], edge) {
		if(parent[cv] != edge-> to) {
			parent[edge->to] = cv;
			if(!containsFriend(g, edge->to))
				edge->useless = true;
			else
				childContainsFriend = true;
		}
	}
	return isFriend[cv] || childContainsFriend;
}


void recorrer(Graph &g, int cv, int &rec, int &h) {
	rec = 0;
	h = 0;
	int i = 0, maxH = 0, maxI;
	FORC(g.edges[cv], edge)
		if (!edge->useless && parent[cv] != edge->to) {
			int ri, hi;
			recorrer(g, edge->to, ri, hi);
			rec += ri;
			hi += edge->weight;
			rec += hi;
			if (maxH < hi) {
				maxH = hi;
				maxI = i;
			}
			i++;
		}
	if (i == 0) return;
	rec -= maxH;
	h = maxH; 
}

mint main() {
	int N, F;
	cin >> N >> F;
	Graph g(N, true);
	FOR(i, 0, N-1) {
		int to, from, w;
		cin >> from >> to >> w;
		g.connect(from - 1, Edge(to-1, w));
	}
	parent[0] = -1;
	FOR(i, 0, F) {
		int k;
		cin >> k;
		isFriend[k-1] =  1;
	}
	containsFriend(g, 0);

	int r, h;
	recorrer(g, 0, r, h);
	cout << r << endl;
} 
