vi low, num, components;
int counter, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int currentVertex) {
    low[currentVertex] = num[currentVertex] = counter++;
    S.push(currentVertex);
    visited[currentVertex] = true;
    FOR(i, 0, g.edges[currentVertex].size()) {
        int neighbor = g.edges[currentVertex][i].to;
        if(num[neighbor] == -1)
            dfs(g, neighbor);
        if(visited[neighbor])
            low[currentVertex] = min(low[currentVertex], low[neighbor]);        
    }
    if(low[currentVertex] == num[currentVertex]) {
        int index = SCCindex++;
        while(true) {
            int v = S.top(); S.pop(); visited[v] = 0;
            components[v] = index;
            if (currentVertex == v)
                break;
        }
    }
}

//the graph must be directed
vi stronglyConnectedComponents(Graph &g)
{
    counter = 0, SCCindex = 0;
    visited = vector<bool>(g.V, 0);
    num = vi(g.V, -1), low = vi(g.V, 0), components = vi(g.V, 0);
    S = stack<int>();
    FOR(i, 0, g.V)
        if(num[i] == -1)
            dfs(g, i);
    return components;
}