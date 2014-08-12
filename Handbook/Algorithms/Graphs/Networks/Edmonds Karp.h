int augment(Graph &g, int flow, vi &parent, int source, int currentVertex, int minEdge) {
	if(currentVertex == source)
		return minEdge;
	if(parent[currentVertex] != -1) {
		flow = augment(g, flow, parent, source, parent[currentVertex], min(minEdge, g.edges[parent[currentVertex]][currentVertex].weight));
		g.edges[parent[currentVertex]][currentVertex].weight -= flow;
		g.edges[currentVertex][parent[currentVertex]].weight += flow;
	}
	return flow;
}

int maxFlow(Graph &g, int source, int sink) {
	int mf = 0, flow = -1;
	while(flow) {
		vi distanceTo(g.V, INF);
		distanceTo[source] = 0;
		queue<int> q; q.push(source);
		vi parent(g.V, -1);
		while(!q.empty()) {
			int currentVertex = q.front(); q.pop();
			if(currentVertex == sink) break;
			FOR(i, 0, g.V) {
				if(g.edges[currentVertex][i].weight > 0 && distanceTo[i] == INF)
					distanceTo[i] = distanceTo[currentVertex] + 1, q.push(i), parent[i] = currentVertex;
			}
		}
		flow = augment(g, 0, parent, source, sink, INF);
		mf += flow;
	}
	return mf;
}