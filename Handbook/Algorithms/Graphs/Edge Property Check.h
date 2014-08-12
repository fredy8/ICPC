#define UNVISITED 0 
#define EXPLORED 1 //visited but not completed
#define VISITED 2 //visited and completed
#define TREE 0 // Edge from explored to unvisited
#define BACK 1 // Edge that is part of a cycle (not including bidirectional edges). From explored to explored
#define FORWARD 2 // Edge from explored to visited
void dfs(Graph &g, int currentVertex, vi &parent, vi &state) {
    state[currentVertex] = EXPLORED;
    FOR(i, 0, g.edges[currentVertex].size()) {
        int neighbor = g.edges[currentVertex][i].to;
        if(state[neighbor] == UNVISITED) {
            g.edges[currentVertex][i].type = TREE;
            parent[neighbor] = currentVertex;
            dfs(g, neighbor, parent, state);
        } else if(state[neighbor] == EXPLORED) {
            if(neighbor != parent[currentVertex]) //if they are equal it is a bidirectional edge
                g.edges[currentVertex][i].type = BACK;
        }
        else if(state[neighbor] == VISITED)
            g.edges[currentVertex][i].type = FORWARD;
    }
    state[currentVertex] = VISITED;
}

void edgeProperties(Graph &g) {
    vi state(g.V, UNVISITED), parent(g.V, 0);
    FOR(i, 0, g.V)
        if(state[i] == UNVISITED)
            dfs(g, i, parent, state);
}