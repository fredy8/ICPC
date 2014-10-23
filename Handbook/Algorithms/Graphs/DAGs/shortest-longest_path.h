vi shortestPath(Graph &g) {
	vi order = topologicalSort(g);
	vi distanceTo(g.V, 0);
	FOR(i, 0, g.V) {
		int cv = order[i];
		FORC(g.edges[cv], edge) {
			if(distanceTo[cv] == 0 && distanceTo[edge->to] == 0)
				distanceTo[edge->to] = INF;
			distanceTo[edge->to] = min(distanceTo[edge->to], edge->weight + distanceTo[cv]);
		}
	}
	return distanceTo;
}
