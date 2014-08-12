vi topologicalSort(Graph &g) {
    vi order;
    int inDegree[g.V];
    FOR(i, 0, g.V) {
    	inDegree[i] = g.nodes[i].inDegree;
        if(inDegree[i] == 0)
            order.push_back(i);
    }
    FOR(i, 0, order.size())
        FOR(j, 0, g.edges[order[i]].size())
            if(--inDegree[g.edges[order[i]][j].to] == 0)
                order.push_back(g.edges[order[i]][j].to);
    return order;
}

void dfs(Graph &g, int currentVertex, vi &order, bool visited[])
{
    visited[currentVertex] = true;
    FOR(i, 0, g.edges[currentVertex].size())
    {
        int neighbor = g.edges[currentVertex][i].to;
        if(!visited[neighbor])
            dfs(g, neighbor, order, visited);
    }
    order.push_back(currentVertex);
}

//Recursive version
vi topologicalSort2(Graph &g)
{
    vi order;
    bool visited[g.V];
    memset(visited, 0, sizeof visited);

    FOR(i, 0, g.V)
        if(visited[i] == 0)
            dfs(g, i, order, visited);

    reverse(order.begin(), order.end());
    return order;
}