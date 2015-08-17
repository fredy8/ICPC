void dfs2(Graph &g, list<int> &path, list<int>::iterator it, int cv) {
	bool last = true;
	FORC(g.edges[cv], edge) {
		if(!edge->visited) {
			last = false;
			edge->visited = 1;
			g.edges[edge->to][edge->backEdge].visited = 1;
			dfs2(g, path, path.insert(it, cv), edge->to);
		}
	}
	if(last) path.insert(path.begin(), cv);
}

//At most two vertices can have odd degree
vi getEulerianPath(Graph &g/*undirected*/, int initial) {
	list<int> path;
	dfs2(g, path, path.begin(), initial);
	if(g.edges[initial].size()%2 == 0)
		path.pop_front();
	vi p;
	FORC(path, it)
		p.pb(*it);
	return reverse(p.begin(), p.end()), p;
}
