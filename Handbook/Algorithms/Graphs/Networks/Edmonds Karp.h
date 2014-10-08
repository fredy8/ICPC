int augment(Graph &g, int flow, vi &parent, int source, int cv, int minEdge) {
	if(cv == source)
		return minEdge;
	if(parent[cv] != -1) {
		flow = augment(g, flow, parent, source, parent[cv], min(minEdge, g.edges[parent[cv]][cv].weight));
		g.edges[parent[cv]][cv].weight -= flow;
		g.edges[cv][parent[cv]].weight += flow;
	}
	return flow;
}

//O(V*E^2)
int maxFlow(Graph &g, int source, int sink) {
	int mf = 0, flow = -1;
	while(flow) {
		vi distanceTo(g.V, INF);
		distanceTo[source] = 0;
		queue<int> q; q.push(source);
		vi parent(g.V, -1);
		while(!q.empty()) {
			int currentVertex = q.front(); q.pop();
			if(currentVertex == sink) break;
			FOR(i, 0, g.V)
				if(g.edges[currentVertex][i].weight > 0 && distanceTo[i] == INF)
					distanceTo[i] = distanceTo[currentVertex] + 1, q.push(i), parent[i] = currentVertex;
		}
		mf += flow = augment(g, 0, parent, source, sink, INF);
	}
	return mf;
}

bool buildLevelGraph(Graph &g, int S, int T, vi &level) {
	queue<int> q; q.push(S);
	level[S] = 1;
	while(!q.empty()) {
		int cv = q.front(); q.pop();
		FOR(to, 0, g.V)
			if(g.edges[cv][to].cap - g.edes[cv][to].flow > 0 || g.edges[to][cv].flow > 0 && !level[to])
				q.push(to), level[to] = level[cv] + 1;
	}
	return level[T];
}

int constructBlockingFlow(Graph &g, int S, int T) {
	int flow = 0;
	stack<int> st; st.push(S);
	vi visited(g.V, 0);
	while(!st.empty()) {
		int cv = st.top(); st.pop();
		if(cv != T) {
			FOR(to, 0, g.V) {
				if(st.top() != T) {
					if(!visited[to] && level[to] == level[cv] + 1) {
						if(g.edges[cv][to].cap - g.edges[cv][to].flow > 0)
							st.push(next), path[next] = cv;
						else if(g.edges[to][cv].flow)
							st.push(next), path[next] = -cv;
					}
				}
			}
			if(st.top() == cv)
				st.pop(), visited[cv] = 1;
		} else {
			int F = INF, bottleneck;
			for(int cur = T; cur != S; cur = abs(path[cur]))
				F = min(F, path[cur] > 0 ? g.edges[path[cur]][cur].cap - g.edges[path[cur]][cur].flow : g.edges[cur][-path[cur]].flow);
			for(int cur = T; cur != S; cur = abs(path[cur])) {
				if(path[cur] > 0) {
					g.edges[path[cur]][cur] += F;
					if(g.edges[path[cur]][cur].cap - g.edges[path[cur]][cur].flow)
						bottleneck = path[cur];
				} else {
					g.edges[path[cur]][cur] += F;
					if(g.edges[cur][-path[cur]] == 0)
						bottleneck = -path[cur];
				}
			}
			while(!st.empty() && st.top() != bottleneck)
				st.pop();
			flow += F;
		}
	}
	return flow;
}

int Dinic(Graph &g, int S, int T) {
	int mf = 0;
	vi level;
	while(level.assign(g.V, 0), buildLevelGraph(g, S, T, level))
		mf += constructBlockingFlow(g, S, T);
	return mf;
}