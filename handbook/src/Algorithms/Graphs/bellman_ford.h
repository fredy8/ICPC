/* Bellman Ford
*/
vi bellmanFord(Graph &g, int source, bool &negativeCycle) {
	vi distanceTo(g.V, INF);
	distanceTo[source] = 0;
	FOR(i, 0, g.V-1)
		FOR(j, 0, g.V)
			FORC(g.edges[j], edge)
				distanceTo[edge->to] = min(distanceTo[edge->to], distanceTo[j] + edge->weight);
	//to detect negative weight cycles:
	FOR(i, 0, g.V)
		FORC(g.edges[i], edge)
			if(distanceTo[edge->to] > distanceTo[i] + edge->weight)
				negativeCycle = true;
	return distanceTo;
}