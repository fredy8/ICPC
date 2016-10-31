struct HeavyLightDecomposition {
	vector<vi> lists;
	vi values, listIndex, posIndex, parent, treeSizes;
	vector<SparseTable> sts;
	LCA *lca;
	HeavyLightDecomposition(Graph &g, vi values) : values(values) {
		lca = new LCA(g, 0);
		listIndex = posIndex = parent = treeSizes = vi(g.V, -1);
		getTreeSizes(g, 0);
		makeLists(g, 0, -1);
		FORC(lists, list) {
			vi v;
			FORC(*list, it) v.pb(values[*it]);
			sts.pb(SparseTable(v));
		}
	}
	~HeavyLightDecomposition() { delete lca; }
	int getTreeSizes(Graph &g, int cv) {
		treeSizes[cv] = 1;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
				parent[edge->to] = cv, treeSizes[cv] += getTreeSizes(g, edge->to);  
		return treeSizes[cv];
	}
	void makeLists(Graph &g, int cv, int listNum) {
		if(listNum == -1)
			listNum = lists.size(), lists.pb(vi());
		listIndex[cv] = listNum;
		posIndex[cv] = lists[listNum].size();
		lists[listNum].pb(cv);
		int MAX = -1;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
			if(MAX == -1 || treeSizes[edge->to] > treeSizes[MAX]) MAX = edge->to;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
			makeLists(g, edge->to, edge->to == MAX ? listNum : -1);	
	}
	int query(int from, int to) {
		int anc = lca->query(from, to), posLeft, posRight;
		int result = min(queryToAncestor(from, anc, posLeft), queryToAncestor(to, anc, posRight));
		if(posLeft < posRight) swap(posLeft, posRight);
		result = min(result, values[lists[listIndex[anc]][sts[listIndex[anc]].query(posIndex[anc], posRight)]]);
		if(posRight != posLeft)
			result = min(result, values[lists[listIndex[anc]][sts[listIndex[anc]].query(posRight+1, posLeft)]]);
		return result;
	}
	int queryToAncestor(int from, int anc, int &posInAncestorList) {
		int result = INF, left = from;
		while(listIndex[left] != listIndex[anc]) {
			result = min(result, values[lists[listIndex[left]][sts[listIndex[left]].query(0, posIndex[left])]]);
			left = parent[lists[listIndex[left]][0]];
		}
		posInAncestorList = posIndex[left];
		return result;
	}
};
