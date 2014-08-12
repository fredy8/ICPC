int *comparator;
bool compare(int a, int b) { return comparator[a] < comparator[b]; }
vi kruskal(vii &edges, int weight[], int V) {
    vi order(edges.size()), minTree;    
    UnionFindDS ds(V);
    comparator = weight;
    FOR(i, 0, order.size()) order[i] = i;
    sort(order.begin(), order.end(), compare);
    for(int i=0; i<int(edges.size()) && int(minTree.size()) < V - 1; i++)
        if(!ds.connected(edges[order[i]].first, edges[order[i]].second)) {
            ds.connect(edges[order[i]].first, edges[order[i]].second);
            minTree.push_back(order[i]);
        }
    return minTree;
}

Graph* comparator;
struct Compare {bool operator()(ii a, ii b) { return comparator->edges[a.first][a.second].weight > comparator->edges[b.first][b.second].weight;}};
vii prim(Graph &g) {
    vi visited(g.V, 0);
    visited[0] = 1;
    vii tree; //list of edges in the MST
    int visitedNodes = 1;
    comparator = &g;
    priority_queue<ii, vector<ii>, Compare> pq;
    int currentVertex = 0;
    while(visitedNodes != g.V) {
        FOR(i, 0, g.edges[currentVertex].size())
            if(!visited[g.edges[currentVertex][i].to])
                pq.push(ii(currentVertex, i));
        ii nextEdge;
        do {
            nextEdge = pq.top();
            pq.pop();
        }while(visited[g.edges[nextEdge.first][nextEdge.second].to] && !pq.empty());
        tree.push_back(nextEdge);
        currentVertex = g.edges[nextEdge.first][nextEdge.second].to;
        visitedNodes++;
        visited[currentVertex] = 1;
    }
    return tree;
}