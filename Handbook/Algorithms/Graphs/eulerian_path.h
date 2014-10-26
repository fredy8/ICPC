void dfs2(Graph &g, list<int> &path, list<int>::iterator it, int cv) {
	bool last = true;
	FORC(g.edges[cv], edge) {
		if(!edge->visited) {
			last = false;
			edge->visited = 1;
			g.edges[edge->to][edge->backEdge].visited = 1;
			/*FORC(g.edges[edge->to], neighborEdge) {
				if(neighborEdge->to == cv && !neighborEdge->visited) {
					g.edges[edge->to][neighborEdge - g.edges[edge->to].begin()].visited = 1;
					break;
				}
			}*/
			dfs2(g, path, path.insert(it, cv), edge->to);
		}
	}
	if(last) path.insert(path.begin(), cv);
}

//At most two vertices can have odd degree
vi getEulerianPath(Graph &g/*undirected*/, int initial) {
	list<int> path;
	dfs2(g, path, path.begin(), initial);
	vi p;
	FORC(path, it)
		p.pb(*it);
	return reverse(p.begin(), p.end()), p;
}
