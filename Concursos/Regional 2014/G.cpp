/*
6
1 3
9 1
11 7
5 7
13 5
4 4
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

struct Star {
	int x, y, i, sec;
	Star() {x = y = i = sec = 0;}
	Star(int x, int y, int i, int s) : x(x), y(y), i(i), sec(s) {}
};

bool compara(Star a, Star b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

double distSq(Star a, Star b) {
	int x = a.x - b.x, y = a.y - b.y;
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
	int N, index[502] = {0};
	cin >> N;
	Graph g(N, true);
	vector<Star> stars;
	vector<vector<Star> > sectors(502, vector<Star>());
	FOR(i, 0, N) {
		Star star;
		cin >> star.x >> star.y;
		star.sec = (star.y-1)/1000 + 1;
		star.i = i;
		stars.pb(star);
		sectors[star.sec].pb(star);
	}
	sort(stars.begin(), stars.end(), compara);
	FOR(i, 1, 501)
		if (sectors[i].size())
			sort(sectors[i].begin(), sectors[i].end(), compara);
	FOR(i, 0, N) {
		Star star = stars[i];
		index[star.sec]++;
		FOR(s, star.sec-1, star.sec+2) {
			FOR(j, index[s], sectors[s].size()) {
				Star other = sectors[s][j];
				if (other.x - star.x > 5) 
					break;
				if (abs(other.y - star.y) > 5)
					continue;
				if (distSq(star, other) <= 25) {
					g.connect(star.i, other.i);
				}
			}
		}
	}

	cout << solve(g) << endl;
}
