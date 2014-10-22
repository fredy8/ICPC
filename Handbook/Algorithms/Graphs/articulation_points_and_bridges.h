//edges[from].back().backEdge = edges[aux].size() - 1; //add this to Graph.connect
//edges[aux].back().backEdge = edges[from].size() - 1; //at the end, inside the if
vi low, num, parent, strongPoints;
int counter, root, rootChildren;
void dfs(Graph &g, int v) {
	low[v] = num[v] = counter++;
	FORC(g.edges[v], edge) {
		if(num[edge->to] == -1) {
			parent[edge->to] = v;
			if(v == root) rootChildren++;
			dfs(g, edge->to);
			if(low[edge->to] >= num[v]) strongPoints[v] = true;
			if(low[edge->to] > num[v]) edge->strong = g.edges[edge->to][edge->backEdge].strong = true;
			low[v] = min(low[v], low[edge->to]);
		} else if(edge->to != parent[v])
			low[v] = min(low[v], num[edge->to]);
	}
}

vi articulationPointsAndBridges(Graph &g /*Undirected*/) {
	counter = 0;
	num = vi(g.V, -1), low = vi(g.V, 0), parent = vi(g.V, -1), strongPoints = vi(g.V, 0);
	FOR(i, 0, g.V)
		if(num[i] == -1) {
			root = i, rootChildren = 0;
			dfs(g, i);
			strongPoints[root] = rootChildren > 1;
		}
	return strongPoints;
}