/*
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
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
    ii ans, left, right; //(number, freq)
    Node() {}
    Node(int pos, int value) {
        ans = left = right = ii(value, 1);
    }
    int getAns() { return ans.second; }
};

vi values;
Node operator+(Node &lNode, Node &rNode) {
    Node merged;
    
    ii ans;
    if(lNode.ans.second > rNode.ans.second)
        ans = lNode.ans;
    else
        ans = rNode.ans;

    if(lNode.right.first == rNode.left.first) {
        int fr = lNode.right.second + rNode.left.second;
        if(fr > ans.second)
            ans = ii(lNode.right.first, fr);
    }

    merged.ans = ans;
    if(lNode.left.first == lNode.right.first && lNode.left.first == rNode.left.first) {
        merged.left = ii(lNode.left.first, lNode.ans.second + rNode.left.second);
    } else {
        merged.left = lNode.left;
    }

    if(rNode.right.first == rNode.left.first && rNode.right.first == lNode.right.first) {
        merged.right = ii(rNode.right.first, rNode.ans.second + lNode.right.second);
    } else {
        merged.right = rNode.right;
    }

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
    int query(int from, int to) {
        // Node n = query(1, 0, values.size()-1, from, to);
        // FOR(i, from, to+1)
        //     cout << values[i] << " ";
        // cout << endl;
        // cout << "---" << endl;
        // cout << n.ans.first << " " << n.ans.second << endl;
        // cout << n.left.first << " " << n.left.second << endl;
        // cout << n.right.first << " " << n.right.second << endl;
        // cout << "---" << endl;

        return query(1, 0, values.size()-1, from, to).getAns(); }
};

int main() {
    int N, Q;
    while(cin >> N >> Q && N) {
        vi nums(N, 0);
        FOR(i, 0, N)
            cin >> nums[i];

        SegmentTree st(nums);
        FOR(i, 0, Q) {
            int from, to;
            cin >> from >> to;
            cout << st.query(from-1, to-1) << endl;
        }
    }
}