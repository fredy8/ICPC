
#define LAZY
vi values;
struct Node {
	int sum;
    Node() { sum = 0; lazy = 0; hasUpdates = false; }
	Node(int value) { sum = 0; lazy = 0; update(0, 0, 0, 0, value); }
	void update(int L, int R, int from, int to, int value) {
		if(from > R || to < L) return;
		sum += (min(to, R) - max(from, L) + 1)*value;
	}
    int ans() { return sum; }
	const Node operator+(const Node &rNode) const {
		Node merged;
		merged.sum = sum + rNode.sum;
		return merged;
	}
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
		if(L != R) {
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
	#else
 	void update(int index, int L, int R, int pos, int value) {
        if (pos > R || pos < L) return;
        if(L == R) { tree[index] = Node(value); return; }
        update(index*2, L, (L+R)/2, index, value);
        update(index*2+1, (L+R)/2+1, R, index, value);
        tree[index] = tree[index*2] + tree[index*2+1];
    }
    void update(int i, int k) { values[i] = k; update(1, 0, values.size()-1, i, k); }
	#endif
	void initialize(int index, int L, int R, int from, int to) {
        if(L == R) { tree[index] = Node(values[L]); return; }
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

