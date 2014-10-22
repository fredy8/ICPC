vi shortestPath(Graph &g) {
	vi order = topologicalSort(g);
	vi distanceTo(g.V, INF);
	FOR(i, 0, g.V) {
		if(g.nodes[order[i]].inDegree == 0)
			distanceTo[order[i]] = 0;
		int cv = order[i];
		FORC(g.edges[cv], edge)
			distanceTo[edge->to] = min(distanceTo[edge->to], edge->weight + distanceTo[cv]);
	}
	return distanceTo;
}