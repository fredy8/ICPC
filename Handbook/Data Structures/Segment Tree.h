int operation(int a, int b) { return a+b; }
//Space: 2*2^(floor(log_2(N))+1)(*2 with lazy propagation)
struct SegmentTree {
private:
    int N;
    vi tree, lazy;
    void update(int treeIndex, int L, int R, int element, int value) {
        if(L == R) {
            tree[treeIndex] = value;
            return;
        }
        if(element <= (L+R)/2)
            update(treeIndex*2, L, (L+R)/2, element, value);
        else if(element >= (L+R)/2 + 1)
            update(treeIndex*2 + 1, (L+R)/2 + 1, R, element, value);
        tree[treeIndex] = operation(tree[treeIndex*2], tree[treeIndex*2 + 1]);
    }
    int query(int treeIndex, int L, int R, int from, int to) {
        if(L >= from && R <= to)
            return tree[treeIndex];
        int left, right;
        bool queryL = false, queryR = false;
        if(from <= (L+R)/2)
            left = query(treeIndex*2, L, (L+R)/2, from, to), queryL = true;
        if(to >= (L+R)/2 + 1)
            right = query(treeIndex*2 + 1, (L+R)/2 + 1, R, from, to), queryR = true;
        if(!queryL) return right;
        else if(!queryR) return left;
        return operation(left, right);
    }
    void rangeUpdate(int treeIndex, int L, int R, int from, int to, int value) {
        if(lazy[treeIndex] != 0) {
            tree[treeIndex] += lazy[treeIndex];
            if(L != R) {
                lazy[treeIndex*2] += lazy[treeIndex];
                lazy[treeIndex*2+1] += lazy[treeIndex];
            }
            lazy[treeIndex] = 0;
        }
        if(L == R) {
            tree[treeIndex] += value;
            return;
        }
        if(L >= from && R <= to) {
            tree[treeIndex] += value*(to-from+1);
            if(L != R) {
                lazy[treeIndex*2] += value;
                lazy[treeIndex*2+1] += value;
            }
            return;
        }
        if(from <= (L+R)/2)
            rangeUpdate(treeIndex*2, L, (L+R)/2, from, to, value);
        if(to >= (L+R)/2 + 1)
            rangeUpdate(treeIndex*2 + 1, (L+R)/2+1, R, from, to, value);
        tree[treeIndex] = operation(tree[treeIndex*2], tree[treeIndex*2 + 1]);
    }
    void initialize(int treeIndex, int L, int R, int from, int to, int values[]) {
        if(L == R) {
            tree[treeIndex] = values[L];
            return;
        }
        if(from <= (L+R)/2)
            initialize(treeIndex*2, L, (L+R)/2, from, to, values);
        if(to >= (L+R)/2 + 1)
            initialize(treeIndex*2 + 1, (L+R)/2+1, R, from, to, values);
        tree[treeIndex] = operation(tree[treeIndex*2], tree[treeIndex*2 + 1]);
    }
public:
    SegmentTree(int values[], int N) : N(N) {
        tree.clear();
        tree.assign(2*(1<<(int(log(N)/log(2))+1)), 0);
        lazy.assign(2*(1<<(int(log(N)/log(2))+1)), 0);
        initialize(1, 0, N-1, 0, N-1, values);
    }
    void update(int i, int k) { update(1, 0, N-1, i, k); }
    int query(int from, int to) { return query(1, 0, N-1, from, to); }
};