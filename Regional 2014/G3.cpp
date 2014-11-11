/*
7
1 3
9 1
11 7
5 7
13 5
4 4
5 10
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

double distSq(ii a, ii b) {
	int x = a.first - b.first, y = a.second - b.second;
	return x*x + y*y;
}

bool visited[50000];
bool color[50000];
int BLACK, WHITE;

void colorG(Graph &g, int cv) {
	visited[cv] = 1;
	(color[cv] ? BLACK : WHITE)++;
	FORC(g.edges[cv], edge) if(!visited[edge->to]) {
		color[edge->to] = !color[cv];
		colorG(g, edge->to);
	}
}

int solve(Graph &g) {
	int ans = 0;
	FOR(i, 0, g.V) 
		if(!visited[i]) {
			BLACK = WHITE = 0;
			colorG(g, i);
			ans += min(BLACK, WHITE);
		}
	
	return ans;
}

mint main() {
	int N;
	cin >> N;
	Graph g(N, true);
	vii stars;
	FOR(i, 0, N) {
		ii star;
		cin >> star.first >> star.second;
		stars.pb(star);
	}
	sort(stars.begin(), stars.end());
	FOR(i, 0, N) {
		FOR(j, i+1, N) {
			if (stars[j].first - stars[i].first > 5) 
				break;
			if (abs(stars[j].second-stars[i].second) > 5)
				continue;
			if (distSq(stars[i], stars[j]) <= 25) {
				g.connect(i, Edge(j));
			}

		}
	}

	cout << solve(g) << endl;
}
