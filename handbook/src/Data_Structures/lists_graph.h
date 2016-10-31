/* Lists Graph
*/
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
