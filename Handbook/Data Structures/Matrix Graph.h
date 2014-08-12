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