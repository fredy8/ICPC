bool isBipartite(Graph &g) {
    queue<int> q;
    q.push(0);
    vi color(g.V, -1);
    color[0] = 0;
    while(!q.empty()) {
        int currentVertex = q.front(); q.pop();
        FOR(i, 0, g.edges[currentVertex].size()) {
            int neighbor = g.edges[currentVertex][i].to;
            if(color[neighbor] == -1) {
                color[neighbor] = !color[currentVertex];
                q.push(neighbor);
            } else if(color[neighbor] == color[currentVertex])
                return false;
        }
    }
    return true;
}