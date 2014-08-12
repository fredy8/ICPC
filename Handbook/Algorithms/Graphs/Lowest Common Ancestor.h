struct LCA {
    vi order, height, index;
    SparseTable *st;
    LCA(Graph &g, int root) {
        index.assign(g.V, -1);
        dfs(g, root, 0, index);
        st = new SparseTable(height);
    }
    ~LCA() { delete st; }
    void dfs(Graph &g, int cv, int h, vi &index) {
        index[cv] = order.size();
        order.push_back(cv), height.push_back(h);
        FOR(i, 0, g.edges[cv].size()) {
            if(index[g.edges[cv][i].to] == -1) {
                dfs(g, g.edges[cv][i].to, height.back() + g.edges[cv][i].weight, index);
                order.push_back(cv), height.push_back(h);
            }
        }
    }
    int query(int i, int j) { return order[st->query(index[i], index[j])]; }
    int distance(int i, int j) { return height[index[i]] + height[index[j]] - 2*(height[index[query(i, j)]]); }
};