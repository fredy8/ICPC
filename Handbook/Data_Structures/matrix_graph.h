struct MatrixEdge {
	int weight;
	MatrixEdge(int weight = 1) : weight(weight) { }
};
struct MatrixGraph {
	int V; bool undirected;
	vector<vector<Edge> > edges;
	MatrixGraph(int v, bool undirected) : V(v), undirected(undirected) {
		edges.assign(V, vector<Edge>(V, Edge(0)));
	}
	void connect(int from, int to, Edge edge = Edge(1)) {
		edges[from][to] = edge;
		if(undirected) edges[to][from] = edge;
	}
};
