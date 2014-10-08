vi topologicalSort(Graph &g) {
    vi order, inDegree(g.V, 0);
    FOR(i, 0, g.V)
        FORC(g.edges[i], it)
            inDegree[it->to]++;
    FOR(i, 0, g.V)
        if(inDegree[i] == 0)
            order.pb(i);
    FOR(i, 0, order.size())
        FORC(g.edges[order[i]], it)
            if(--inDegree[it->to] == 0)
                order.pb(it->to);
    return order;
}

void dfs(Graph &g, int currentVertex, vi &order, vi &visited) {
    visited[currentVertex] = true;
    FORC(g.edges[currentVertex], it)
        if(!visited[it->to])
            dfs(g, it->to, order, visited);
    order.pb(currentVertex);
}

//Recursive version
vi topologicalSort2(Graph &g) {
    vi order, visited(g.V, 0);
    FOR(i, 0, g.V)
        if(!visited[i])
            dfs(g, i, order, visited);
    reverse(order.begin(), order.end());
    return order;
}