/* Topological Sort
*/
vi topologicalSort(Graph &g) {
	vi order, inDegree(g.V, 0);
	FOR(i, 0, g.V)
		FORC(g.edges[i], edge)
			inDegree[edge->to]++;
	FOR(i, 0, g.V)
		if(inDegree[i] == 0)
			order.pb(i);
	FOR(i, 0, order.size())
		FORC(g.edges[order[i]], edge)
			if(--inDegree[edge->to] == 0)
				order.pb(edge->to);
	return order;
}

void dfs(Graph &g, int currentVertex, vi &order, vi &visited) {
	visited[currentVertex] = true;
	FORC(g.edges[currentVertex], edge)
		if(!visited[edge->to])
			dfs(g, edge->to, order, visited);
	order.pb(currentVertex);
}

//Recursive version
vi topologicalSort2(Graph &g) {
	vi order, visited(g.V, 0);
	FOR(i, 0, g.V)
		if(!visited[i])
			dfs(g, i, order, visited);
	reverse(order.begin(), order.end());
	return order;
}