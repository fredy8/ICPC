void DFS(Graph &g, int currentVertex, int visited[]) {
    visited[currentVertex] = 1;
    FOR(i, 0, g.edges[currentVertex].size()) {
        int neighbor = g.edges[currentVertex][i].to;
        if(!visited[neighbor]) DFS(g, neighbor, visited);
    }
}