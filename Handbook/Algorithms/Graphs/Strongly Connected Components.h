vi low, num, components;
int counter, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int cv) {
	low[cv] = num[cv] = counter++;
	S.push(cv);
	visited[cv] = true;
	FORC(g.edges[cv], edge) {
		if(num[edge->to] == -1)
			dfs(g, edge->to);
		if(visited[edge->to])
			low[cv] = min(low[cv], low[edge->to]);        
	}
	if(low[cv] == num[cv]) {
		int index = SCCindex++;
		while(true) {
			int v = S.top(); S.pop(); visited[v] = 0;
			components[v] = index;
			if (cv == v)
				break;
		}
	}
}

vi stronglyConnectedComponents(Graph &g/*directed*/) {
	counter = 0, SCCindex = 0;
	visited = vector<bool>(g.V, 0);
	num = vi(g.V, -1), low = vi(g.V, 0), components = vi(g.V, 0);
	S = stack<int>();
	FOR(i, 0, g.V)
		if(num[i] == -1)
			dfs(g, i);
	return components;
}