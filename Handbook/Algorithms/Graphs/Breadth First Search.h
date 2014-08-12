void BFS(Graph &g, int startingVertex) {
    vector<bool> visited(g.V, 0);
    visited[startingVertex] = 1;
    queue<int> q; q.push(startingVertex);
    while(!q.empty()) {
        int currentVertex = q.front(); q.pop();
        FOR(i, 0, g.edges[currentVertex].size()) {
            int neighbor = g.edges[currentVertex][i].to;
            if(!visited[neighbor]) {
                visited[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }
}