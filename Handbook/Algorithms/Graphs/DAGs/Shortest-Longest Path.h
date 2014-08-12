vi shortestPath(Graph &g) {
    vi order = topologicalSort(g);
    vi distanceTo(g.V, INF);
    FOR(i, 0, g.V) {
        if(g.nodes[order[i]].inDegree == 0)
            distanceTo[order[i]] = 0;
        int currentVertex = order[i];
        FOR(j, 0, g.edges[currentVertex].size()) {
            int neighbor = g.edges[currentVertex][j].to;
            distanceTo[neighbor] = min(distanceTo[neighbor], g.edges[currentVertex][j].weight + distanceTo[currentVertex]);
        }
    }
    return distanceTo;
}