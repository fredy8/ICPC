vi dijkstra(Graph &g, int src) {
	vi dist(g.V, INF);
	dist[src] = 0;
	priority_queue<ii, vii, greater<ii> > pq;
	pq.push(ii(0, src));
	while(!pq.empty()) {
		int cv = pq.top().second;
		int d = pq.top().first;
		pq.pop();
		if(d > dist[cv]) continue;
		FORC(g.edges[cv], edge)
			if(dist[edge->to] > dist[cv] + edge->weight) {
				dist[edge->to] = dist[cv] + edge->weight;
				pq.push(ii(dist[edge->to], edge->to));
			}
	}
	return dist;
}