struct UnionFindDS {
    vi tree;
    UnionFindDS(int n) { FOR(i, 0, n) tree.push_back(i); }
    int root(int i) { return tree[i] == i ? i : tree[i] = root(tree[i]); }
    bool connected(int i, int j) {return root(i) == root(j);}
    void connect(int i, int j) { tree[root(i)] = tree[root(j)]; }
};

struct UnionFindDS {
    vi tree, sizes;
    int N;
    UnionFindDS(int n) : N(n) {
        tree.reserve(n);
        FOR(i, 0, n) tree[i] = i;
        sizes.assign(n, 1);
    }
    int root(int i) { return (tree[i] == i) ? i : (tree[i] = root(tree[i]));}
    int countSets() { return N;}
    int getSize(int i) { return sizes[root(i)];}
    bool connected(int i, int j) { return root(i) == root(j);}
    void connect(int i, int j) {
        int ri = root(i), rj = root(j);
        if(ri != rj) {
            N--;
            sizes[rj] += sizes[ri];
            tree[ri] = rj;
        }
    }
};

