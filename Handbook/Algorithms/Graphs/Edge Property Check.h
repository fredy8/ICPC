#define UNVISITED 0 
#define EXPLORED 1 //visited but not completed
#define VISITED 2 //visited and completed
#define TREE 0 // Edge from explored to unvisited
#define BACK 1 // Edge that is part of a cycle (not including bidirectional edges). From explored to explored
#define FORWARD 2 // Edge from explored to visited
void dfs(Graph &g, int cv, vi &parent, vi &state) {
	state[cv] = EXPLORED;
	FORC(g.edges[cv], edge)
		if(state[edge->to] == UNVISITED) {
			edge->type = TREE;
			parent[edge->to] = cv;
			dfs(g, edge->to, parent, state);
		} else if(state[edge->to] == EXPLORED)
			edge->type = BACK; //if(edge->to == parent[cv]) //bidirectional
		else if(state[edge->to] == VISITED)
			edge->type = FORWARD;
	state[cv] = VISITED;
}

void edgeProperties(Graph &g) {
	vi state(g.V, UNVISITED), parent(g.V, 0);
	FOR(i, 0, g.V)
		if(state[i] == UNVISITED)
			dfs(g, i, parent, state);
}