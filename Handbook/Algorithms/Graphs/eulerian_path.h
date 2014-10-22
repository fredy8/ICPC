void dfs(Graph &g, list<int> &path, list<int>::iterator it, int cv) {
	bool last = true;
	FORC(g.edges[cv], edge) {
		if(!edge->visited) {
			last = false;
			edge->visited = 1;
			FORC(g.edges[edge->to], neighborEdge) {
				if(neighborEdge->to == cv && !neighborEdge->visited) {
					g.edges[edge->to][j].visited = 1;
					break;
				}
			}
			dfs(g, path, path.insert(it, cv), edge->to);
		}
	}
	if(last) path.insert(path.begin(), cv);
}

vi getEulerianPath(Graph &g/*undirected*/, int initial) {
	list<int> path;
	dfs(g, path, path.begin(), initial);
	vi p;
	FORC(path, it)
		p.pb(*it);
	return reverse(p.begin(), p.end()), p;
}