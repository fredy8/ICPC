struct Edge {
    int to, weight;
    Edge(int to, int weight = 1) : to(to), weight(weight) {}
};
struct Graph {
    int V; bool undirected;
    vector<vector<Edge> > edges;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
    void connect(int from, Edge edge) {
        edges[from].pb(edge);
        if(undirected) {
            int aux = edge.to;
            edge.to = from;
            edges[aux].pb(edge);
        }
    }
};