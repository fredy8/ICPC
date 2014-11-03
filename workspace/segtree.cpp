/*
10 10
7 7 3 3 5 9 9 8 1 8 
QUERY 6 6 
UPDATE 3 4 
QUERY 0 1 
QUERY 0 5 
QUERY 4 7 
QUERY 3 5 
QUERY 0 2 
QUERY 4 6 
UPDATE 6 10 
QUERY 0 9
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#define INF 1000000000
#define FOR(i, a, b) for(ll i=ll(a); i<ll(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int size(ii a) {
	return a.second - a.first + 1;
}


ii max(ii a, ii b) {
	return size(a) > size(b) ? a : b;
}

vi values;
struct Node {
	ii left, right, MAX;
    Node() { }
	Node(int pos, int value) { update(pos, pos, pos, pos, value); }
	void update(int L, int R, int from, int to, int value) {
		MAX = left = right = ii(L, L);
	}
    int ans() { return size(MAX); }
	Node operator+(Node &rNode) {
		Node merged;

		merged.MAX = max(MAX, rNode.MAX);
		if(right.second + 1 == rNode.left.first && values[right.second] < values[rNode.left.first]) {
			merged.MAX = max(merged.MAX, ii(right.first, rNode.left.second));
		}

		merged.left = left;
		if(rNode.left.first == left.second + 1 && values[left.second] < values[rNode.left.first])
			merged.left = ii(left.first, rNode.left.second);

		merged.right = rNode.right;
		if(rNode.right.first == right.second + 1 && values[right.second] < values[rNode.right.first])
			merged.right = ii(right.first, rNode.right.second);
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
        if(L == R) { tree[index] = Node(L, value); return; }
        update(index*2, L, (L+R)/2, index, value);
        update(index*2+1, (L+R)/2+1, R, index, value);
        tree[index] = tree[index*2] + tree[index*2+1];
    }
    void update(int i, int k) { values[i] = k; update(1, 0, values.size()-1, i, k); }
	#endif
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


int main() {
	int N, Q;
	while(cin >> N >> Q) {
		vi A;
		FOR(i, 0, N) {
			int k; cin >> k;
			A.pb(k);
		}
		SegmentTree st(A);

		FOR(i, 0, Q) {
			string type;
			int a, b;
			cin >> type >> a >> b;
			if(type == "QUERY") {
				cout << st.query(a, b) << endl;
			} else {
				st.update(a, b);
			}
																																																		        }
	}
}
