/* Edmonds-Karp
O(VE^2)
Finds a the maxflow from source to sink of a directed graph.
The weight of an edge denotes the capacity of the edge.
The negative weight edges are the edges with flow.
*/
int augment(MatrixGraph &g, int flow, vi &parent, int source, int cv, int minEdge) {
	if(cv == source)
		return minEdge;
	if(parent[cv] != -1) {
		flow = augment(g, flow, parent, source, parent[cv], min(minEdge, g.edges[parent[cv]][cv].weight));
		g.edges[parent[cv]][cv].weight -= flow;
		g.edges[cv][parent[cv]].weight += flow;
	}
	return flow;
}

int maxFlow(MatrixGraph &g, int source, int sink) {
	int mf = 0, flow = -1;
	while(flow) {
		vi distanceTo(g.V, INF);
		distanceTo[source] = 0;
		queue<int> q; q.push(source);
		vi parent(g.V, -1);
		while(!q.empty()) {
			int cv = q.front(); q.pop();
			if(cv == sink) break;
			FOR(i, 0, g.V)
				if(g.edges[cv][i].weight > 0 && distanceTo[i] == INF)
					distanceTo[i] = distanceTo[cv] + 1, q.push(i), parent[i] = cv;
		}
		mf += flow = augment(g, 0, parent, source, sink, INF);
	}
	return mf;
}
