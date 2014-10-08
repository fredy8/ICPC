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

struct Node {
    ii left, ii right, ii MAX;
    Node() {}
    Node(int pos, int value) {}
    int ans() {
        return 0;
    }
};

vi values; //only works w/o lazy propagation
Node operator+(Node &lNode, Node &rNode) {
    Node merged;
    merged.sum = lNode.sum + rNode.sum;
    return merged;
}

struct SegmentTree {
    vector<Node> tree;
    vector<queue<ii> > lazy;
    Node query(int treeIndex, int L, int R, int from, int to) {
        if(L >= from && R <= to)
            return tree[treeIndex];
        Node left, right;
        bool queryL = false, queryR = false;
        if(from <= (L+R)/2)
            left = query(treeIndex*2, L, (L+R)/2, from, to), queryL = true;
        if(to >= (L+R)/2 + 1)
            right = query(treeIndex*2 + 1, (L+R)/2 + 1, R, from, to), queryR = true;
        if(!queryL) return right;
        if(!queryR) return left;
        return left + right;
    }
    void pointUpdate(int treeIndex, int L, int R, int index, Node &value) {
        if (index > R || index < L)
            return;
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
        lazy.assign(2*(1<<(int(log(N)/log(2))+1)), Node());
        values = vi(A.begin(), A.end());
        initialize(1, 0, N-1, 0, N-1);
    }
    void pointUpdate(int i, int k) { Node n(i, k); values[i] = k; pointUpdate(1, 0, values.size()-1, i, n); }
    int query(int from, int to) { return query(1, 0, values.size()-1, from, to).ans(); }
};

int main() {
    int N;
    cin >> N;
    int arr[N];
    FOR(i, 0, N)
        cin >> arr[i];

    SegmentTree st(arr, N);

    int Q; cin >> Q;
    FOR(i, 0, Q) {
        int from, to;
        cin >> from >> to;
        cout << st.query(from-1, to-1) << endl;
    }
}