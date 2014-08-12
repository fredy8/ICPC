vi bellmanFord(Graph &g, int source, bool &negativeCycle) {
    vi distanceTo(g.V, INF);
    distanceTo[source] = 0;
    FOR(i, 0, g.V-1)
        FOR(j, 0, g.V)
            FOR(k, 0, g.edges[j].size())
                distanceTo[g.edges[j][k].to] = min(distanceTo[g.edges[j][k].to], distanceTo[j] + g.edges[j][k].weight);
    //to detect negative weight cycles:
    FOR(i, 0, g.V)
        FOR(j, 0, g.edges[i].size())
            if(distanceTo[g.edges[i][j].to] > distanceTo[i] + g.edges[i][j].weight)
                negativeCycle = true;
    return distanceTo;
}