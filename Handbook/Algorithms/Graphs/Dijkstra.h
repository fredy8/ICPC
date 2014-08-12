vi dijkstra(Graph &g, int source) {
    vi distanceTo(g.V, INF);
    distanceTo[source] = 0;
    priority_queue<ii, vii, greater<ii> > pq;
    pq.push(ii(0, source));
    while(!pq.empty()) {
        int currentVertex = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if(d > distanceTo[currentVertex]) continue;
        FOR(i, 0, g.edges[currentVertex].size()) {
            int neighbor = g.edges[currentVertex][i].to;
            if(distanceTo[neighbor] > distanceTo[currentVertex] + g.edges[currentVertex][i].weight) {
                distanceTo[neighbor] = distanceTo[currentVertex] + g.edges[currentVertex][i].weight;
                pq.push(ii(distanceTo[neighbor], neighbor));
            }
        }
    }
    return distanceTo;
}