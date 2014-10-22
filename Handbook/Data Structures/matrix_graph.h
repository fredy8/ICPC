struct Edge {
	int weight;
	Edge(int weight = 1) : weight(weight) { }
};
struct Graph {
	int V; bool undirected;
	vector<vector<Edge> > edges;
	Graph(int v, bool undirected) : V(v), undirected(undirected) {
		edges.assign(V, vector<Edge>(V, Edge(0)));
	}
	void connect(int from, int to, int weight = 1) {
		edges[from][to].weight = weight;
		if(undirected) edges[to][from].weight = weight;
	}
};