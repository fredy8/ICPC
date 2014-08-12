void dfs(Graph &g, list<int> &path, list<int>::iterator it, int currentVertex) {
    bool last = true;
    FOR(i, 0, g.edges[currentVertex].size()) {
        int neighbor = g.edges[currentVertex][i].to;
        if(!g.edges[currentVertex][i].visited) {
            last = false;
            g.edges[currentVertex][i].visited = 1;
            FOR(j, 0, g.edges[neighbor].size()) {
                int neighborOfNeighbor = g.edges[neighbor][j].to;
                if(neighborOfNeighbor == currentVertex && !g.edges[neighbor][j].visited) {
                    g.edges[neighbor][j].visited = 1;
                    break;
                }
            }
            dfs(g, path, path.insert(it, currentVertex), neighbor);
        }
    }
    if(last) path.insert(path.begin(), currentVertex);
}

//only for undirected graphs
vi getEulerianPath(Graph &g, int initial)
{
    list<int> path;
    dfs(g, path, path.begin(), initial);
    vi p;
    for(list<int>::iterator it=path.begin(); it!=path.end(); it++)
        p.push_back(*it);
    reverse(p.begin(), p.end());
    return p;
}