vi values;
struct Node {
	int sum;
    Node() { init(); }
	Node(int pos, int value) { init(); update(0, 0, 0, 0, value); }
	void init() {
		sum = 0;
		#ifdef LAZY
		lazy = 0; hasUpdates = false;
		#endif
	}
	void update(int L, int R, int from, int to, int value) {
		if(from > R || to < L) return;
		sum += (min(to, R) - max(from, L) + 1)*value;
	}
    int ans() { return sum; }
	Node operator+(Node &rNode) { return Node(0, sum + rNode.sum); }
	#ifdef LAZY
	int lazy; bool hasUpdates;
	void storeUpdate(int value) { lazy += value; hasUpdates = true; }
	void applyUpdates(int L, int R) { if(hasUpdates) update(L, R, L, R, lazy); lazy = 0; hasUpdates = false; } 
	int getUpdates() { return lazy; }
	#endif
};
struct SegmentTree {
    vector<Node> tree;
    Node query(int index, int L, int R, int from, int to) {
		#ifdef LAZY
		if(L != R && tree[index].hasUpdates) {
			update(index*2, L, (L+R)/2, 0, values.size(), tree[index].getUpdates());
			update(index*2+1, (L+R)/2+1, R, 0, values.size(), tree[index].getUpdates());
		}
		tree[index].applyUpdates(L, R);
		#endif
		if(L >= from && R <= to) return tree[index];
        Node left, right;
        bool queryL = false, queryR = false;
        if(from <= (L+R)/2) left = query(index*2, L, (L+R)/2, from, to), queryL = true;
        if(to >= (L+R)/2+1) right = query(index*2+1, (L+R)/2+1, R, from, to), queryR = true;
		return !queryL ? right : (!queryR ? left : left + right);
    }
	int query(int from, int to) { return query(1, 0, values.size()-1, from, to).ans(); }
	#ifdef LAZY
	void update(int index, int L, int R, int from, int to, int value) {
        if (from > R || to < L) return;
        if(L >= from && R <= to) { tree[index].storeUpdate(value); return; }
		tree[index].update(L, R, from, to, value);
        update(index*2, L, (L+R)/2, from, to, value);
        update(index*2+1, (L+R)/2+1, R, from, to, value);
	}
	void update(int from, int to, int value) { update(1, 0, values.size()-1, from, to, value); }
	#endif
 	void pointUpdate(int index, int L, int R, int pos, int value) {
        if (pos > R || pos < L) return;
        if(L == R) { tree[index] = Node(pos, value); return; }
        pointUpdate(index*2, L, (L+R)/2, pos, value);
        pointUpdate(index*2+1, (L+R)/2+1, R, pos, value);
        tree[index] = tree[index*2] + tree[index*2+1];
    }
    void pointUpdate(int i, int k) { values[i] = k; pointUpdate(1, 0, values.size()-1, i, k); }
	void initialize(int index, int L, int R, int from, int to) {
        if(L == R) { tree[index] = Node(L, values[L]); return; }
        initialize(index*2, L, (L+R)/2, from, to);
        initialize(index*2+1, (L+R)/2+1, R, from, to);
        tree[index] = tree[index*2] + tree[index*2+1];
    }
	SegmentTree(vi A) {
        tree.clear();
        tree.assign(2*(1<<(int(log(A.size())/log(2))+1)), Node());
        values = vi(A.begin(), A.end());
        initialize(1, 0, A.size()-1, 0, A.size()-1);
    }
};
