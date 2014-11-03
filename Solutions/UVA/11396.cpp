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
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
    int to, weight;
    Edge(int to, int weight = 1) : to(to), weight(weight) {}
};
struct Graph {
    int V;
    vector<vector<Edge> > edges;
    bool undirected;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
    void connect(int from, Edge edge) {
        edges[from].push_back(edge);
        if(undirected) {
            int aux = edge.to;
            edge.to = from;
            edges[aux].push_back(edge);
        }
    }
};

bool isBipartite(Graph &g) {
    queue<int> q;
    q.push(0);
    vi color(g.V, -1);
    color[0] = 0;
    while(!q.empty()) {
        int currentVertex = q.front(); q.pop();
        FOR(i, 0, g.edges[currentVertex].size()) {
            int neighbor = g.edges[currentVertex][i].to;
            if(color[neighbor] == -1) {
                color[neighbor] = !color[currentVertex];
                q.push(neighbor);
            } else if(color[neighbor] == color[currentVertex])
                return false;
        }
    }
    return true;
}

int main() {
	int V;
	
	
	while(cin >> V, V) {
		Graph g(V, true);
		int a,b;
		
		while(cin >> a >> b, a) {
			g.connect(a-1,b-1);
		}
		
		cout << (isBipartite(g) ? "YES" : "NO") << endl;
	}
}
