vi low, num, parent, strongPoints;
int counter, root, rootChildren;

void dfs(Graph &g, int v) {
    low[v] = num[v] = counter++;
    FOR(i, 0, g.edges[v].size()) {
        int neighbor = g.edges[v][i].to;
        if(num[neighbor] == -1) {
            parent[neighbor] = v;
            if(v == root)
                rootChildren++;
            dfs(g, neighbor);
            if(low[neighbor] >= num[v])
                strongPoints[v] = true;
            if(low[neighbor] > num[v])
                g.edges[v][i].strong = true;
            low[v] = min(low[v], low[neighbor]);
        } else if(neighbor != parent[v])
            low[v] = min(low[v], num[neighbor]);
    }
}

//Must be an undirected graph
vi articulationPointsAndBridges(Graph &g) {
    counter = 0;
    num = vi(g.V, -1), low = vi(g.V, 0), parent = vi(g.V, -1), strongPoints = vi(g.V, 0);
    FOR(i, 0, g.V)
        if(num[i] == -1) {
            root = i, rootChildren = 0;
            dfs(g, i);
            strongPoints[root] = rootChildren > 1;
        }
    return strongPoints;
}