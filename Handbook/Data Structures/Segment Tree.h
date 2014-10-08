struct Node {
	Node() {}
	Node(int pos, int value) {}
	int ans() { return 0; }
};

vi values;
Node operator+(Node &lNode, Node &rNode) {
	Node merged;
	//Merge operation
	return merged;
}

struct SegmentTree {
	vector<Node> tree;
	Node query(int treeIndex, int L, int R, int from, int to) {
		if(L >= from && R <= to) return tree[treeIndex];
		Node left, right;
		bool queryL = false, queryR = false;
		if(from <= (L+R)/2) left = query(treeIndex*2, L, (L+R)/2, from, to), queryL = true;
		if(to >= (L+R)/2 + 1) right = query(treeIndex*2 + 1, (L+R)/2 + 1, R, from, to), queryR = true;
		if(!queryL) return right;
		if(!queryR) return left;
		return left + right;
	}
	void pointUpdate(int treeIndex, int L, int R, int index, Node &value) {
		if (index > R || index < L) return;
		if(L == R) {
			tree[treeIndex] = value;
			return;
		}
		pointUpdate(treeIndex*2, L, (L+R)/2, index, value);
		pointUpdate(treeIndex*2 + 1, (L+R)/2 + 1, R, index, value);
		tree[treeIndex] = tree[treeIndex*2] + tree[treeIndex*2 + 1];
	}
	void initialize(int treeIndex, int L, int R, int from, int to) {
		if(L == R) {
			tree[treeIndex] = Node(L, values[L]);
			return;
		}
		initialize(treeIndex*2, L, (L+R)/2, from, to);
		initialize(treeIndex*2 + 1, (L+R)/2+1, R, from, to);
		tree[treeIndex] = tree[treeIndex*2] + tree[treeIndex*2 + 1];
	}
	SegmentTree(vi A) {
		tree.clear();
		int N = A.size();
		tree.assign(2*(1<<(int(log(N)/log(2))+1)), Node());
		values = vi(A.begin(), A.end());
		initialize(1, 0, N-1, 0, N-1);
	}
	void pointUpdate(int i, int k) { Node n(i, k); values[i] = k; pointUpdate(1, 0, values.size()-1, i, n); }
	int query(int from, int to) { return query(1, 0, values.size()-1, from, to).ans(); }
};