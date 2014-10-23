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
	void connect(int from, int to, int weight = 1) {
		edges[from][to].weight = weight;
		if(undirected) edges[to][from].weight = weight;
	}
};
