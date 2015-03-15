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
#include <unordered_map>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
    int weight;
    Edge(int weight = 1) : weight(weight) { }
};
struct Graph {
    int V;
    vector<vector<Edge> > edges;
    bool undirected;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) {
        edges.assign(V, vector<Edge>(V, 0));
    }
    void connect(int from, int to, Edge edge = Edge()) {
        edges[from][to] = edge;
        if(undirected) edges[to][from] = edge;
    }
};

int augment(Graph &g, int flow, vi &parent, int source, int currentVertex, int minEdge) {
	if(currentVertex == source)
		return minEdge;
	if(parent[currentVertex] != -1) {
		flow = augment(g, flow, parent, source, parent[currentVertex], min(minEdge, g.edges[parent[currentVertex]][currentVertex].weight));
		g.edges[parent[currentVertex]][currentVertex].weight -= flow;
		g.edges[currentVertex][parent[currentVertex]].weight += flow;
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
			FOR(i, 0, g.V) {
				if(g.edges[currentVertex][i].weight > 0 && distanceTo[i] == INF)
					distanceTo[i] = distanceTo[currentVertex] + 1, q.push(i), parent[i] = currentVertex;
			}
		}
		flow = augment(g, 0, parent, source, sink, INF);
		mf += flow;
	}
	return mf;
}

#define S 0
#define T 37
#define APP(x) (1 + (x) - 'A')
#define CPU(x) (27 + (x) - '0')
#define CPUi(x) (27 + (x))

int main() {
	string line;
	
	while(getline(cin, line)) {
		Graph g(40, false);
		int total = 0;
		do {
			string a, b;
			stringstream ss(line);
			ss >> a >>b;
			
			g.connect(S, APP(a[0]), Edge(a[1] - '0'));
			total += a[1] - '0';
			
			FOR(i, 0, b.size()) {
				if(isdigit(b[i])) {
					g.connect(APP(a[0]), 
						CPU(b[i]), 
						Edge(INF));
				}
			}
		} while (getline(cin, line) && line != "");
		
		FOR(i, 0, 10) {
			g.connect(CPUi(i), T, Edge(1));
		}
		
		int f = maxFlow(g, S, T);
		
		if(f == total) {
			bool could = false;
			
			FOR(i, 27, 37) {
				bool assigned = false;
				FOR(j, 1, 27) {
					if(g.edges[i][j].weight) { // backflow
						could = true;
						assigned = true;
						cout << (char)(j - 1 + 'A');
					}
					
				}
				if(!assigned) cout << "_";
			}
		} else cout << "!";
		cout << endl;
	}
}
