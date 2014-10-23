/*
3 5
2 1 5
3 5 2 3
3 3 2 4
5 11
2 10 11
4 1 3 5 7
6 2 3 4 5 6 7
4 3 5 7 9
3 8 1 5
6 31
9 1 2 3 15 20 25 30 9 10
10 2 25 7 9 3 11 12 13 14 4
10 11 12 13 14 4 16 17 18 19 5
2 5 7
9 21 22 23 24 26 27 28 29 7
3 22 6 21


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
    int backEdge, strong; //optional
	Edge(int to, int weight = 1) : to(to), weight(weight), strong(0) {}
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

mint main() {
	int A, N;
	while(cin >> A >> N) {
	Graph g(A+N, true);

	queue<ii> q;

	FOR(i, 0, A) {
		int auths;
		cin >> auths;
		while(auths--) {
			int auth;
			cin >> auth;
			g.connect(N+i, Edge(auth-1));
		}
	}

	vi visited(A+N, 0);
	visited[0] = 1;
	q.push(ii(0, 0));
	int count = 0, MAX = 0, S = 0;
	while(!q.empty()) {
		ii cv = q.front();
		q.pop();
		if(cv.second%2 == 0) {
			S += cv.second/2;
			MAX = cv.second/2;
			count++;
		}
		FORC(g.edges[cv.first], edge) {
			if(!visited[edge->to])
				visited[edge->to] = 1, q.push(ii(edge->to, cv.second+1));
		}
	}

	cout << count << " " << MAX << " " << S << endl;
}

}
