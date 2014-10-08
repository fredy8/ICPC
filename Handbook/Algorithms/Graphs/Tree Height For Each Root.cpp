int getLongestPathDown(Graph &g, int cv, vii &longestPathDown, vii &secondLongestPathDown, vi &parent) {
	FORC(g.edges[cv], edge) {
		if(edge->to != parent[cv]) {
			parent[edge->to] = cv;
			int pathDownLength = 1 + getLongestPathDown(g, edge->to, longestPathDown, secondLongestPathDown, parent);
			if(pathDownLength > longestPathDown[cv].second) {
				secondLongestPathDown[cv] = longestPathDown[cv];
				longestPathDown[cv] = ii(edge->to, pathDownLength);
			} else if(pathDownLength > secondLongestPathDown[cv].second) {
				secondLongestPathDown[cv] = ii(edge->to, pathDownLength);
			}
		}
	}
	return longestPathDown[cv].second;
}

void getLongestPath(Graph &g /*unrooted tree*/, vii &longestPath) {
	longestPath.assign(g.V, ii(-1, 0));
	vii longestPathDown(g.V, ii(-1, 1)), secondLongestPathDown(g.V, ii(-1, 1)), secondLongestPath(g.V, ii(-1, 0));
	vi parent(g.V, -1);
	getLongestPathDown(g, 0, longestPathDown, secondLongestPathDown, parent);
	queue<int> q;
	q.push(0);
	while(!q.empty()) {
		int cv = q.front(); q.pop();
		FORC(g.edges[cv], edge)
			if(edge->to != parent[cv]) 
				q.push(edge->to);
		if(parent[cv] == -1) {
			longestPath[cv] = longestPathDown[cv];
			secondLongestPath[cv] = secondLongestPathDown[cv];
		} else {
			ii longestPathThroughParent = ii(parent[cv], (longestPath[parent[cv]].first != cv ? longestPath[parent[cv]].second : secondLongestPath[parent[cv]].second)+1);
			if(longestPathThroughParent.second >= longestPathDown[cv].second) {
				longestPath[cv] = longestPathThroughParent;
				secondLongestPath[cv] = longestPathDown[cv];
			} else if(longestPathThroughParent.second >= secondLongestPathDown[cv].second) {
				longestPath[cv] = longestPathDown[cv];
				secondLongestPath[cv] = longestPathThroughParent;
			} else {
				longestPath[cv] = longestPathDown[cv];
				secondLongestPath[cv] = secondLongestPathDown[cv];
			}
		}
	}
}