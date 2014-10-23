int *comparator1;
bool compare(int a, int b) { return comparator1[a] < comparator1[b]; }
vi kruskal(vii &edges, int weight[], int V) {
	vi order(edges.size()), minTree;    
	UnionFindDS ds(V);
	comparator1 = weight;
	FOR(i, 0, order.size()) order[i] = i;
	sort(order.begin(), order.end(), compare);
	for(int i=0; i<int(edges.size()) && int(minTree.size()) < V - 1; i++)
		if(!ds.connected(edges[order[i]].first, edges[order[i]].second)) {
			ds.connect(edges[order[i]].first, edges[order[i]].second);
			minTree.pb(order[i]);
		}
	return minTree;
}

Graph* comparator2;
struct Compare { bool operator()(ii a, ii b) { return comparator2->edges[a.first][a.second].weight > comparator2->edges[b.first][b.second].weight;} };
vii prim(Graph &g) {
	vi visited(g.V, 0);
	visited[0] = 1;
	vii tree; //list of edges in the MST
	int visitedNodes = 1;
	comparator2 = &g;
	priority_queue<ii, vector<ii>, Compare> pq;
	int cv = 0;
	while(visitedNodes != g.V) {
		FORC(g.edges[cv], edge)
			if(!visited[edge->to])
				pq.push(ii(cv, edge - g.edges[cv].begin()));
		ii nextEdge;
		do {
			nextEdge = pq.top();
			pq.pop();
		} while(visited[g.edges[nextEdge.first][nextEdge.second].to] && !pq.empty());
		tree.pb(nextEdge);
		cv = g.edges[nextEdge.first][nextEdge.second].to;
		visitedNodes++;
		visited[cv] = 1;
	}
	return tree;
}
