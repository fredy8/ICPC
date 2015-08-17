struct LCA {
	vi order, height, index;
	SparseTable *st;
	LCA(Graph &g, int root) {
		index.assign(g.V, -1);
		dfs(g, root, 0, index);
		st = new SparseTable(height);
	}
	~LCA() { delete st; }
	void dfs(Graph &g, int cv, int h, vi &index) {
		index[cv] = order.size();
		order.pb(cv), height.pb(h);
		FORC(g.edges[cv], edge)
			if(index[edge->to] == -1) {
				dfs(g, edge->to, height.back() + edge->weight, index);
				order.pb(cv), height.pb(h);
			}
	}
	int query(int i, int j) { return order[st->query(index[i], index[j])]; }
	int distance(int i, int j) { return height[index[i]] + height[index[j]] - 2*(height[index[query(i, j)]]); }
};