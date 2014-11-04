/*
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5
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
#include <list>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

//Space: 2*2^(floor(log_2(N))+1)
struct SegmentTree {
private:
    int N;
    vi tree;
    void update(int treeIndex, int L, int R, int element, int value) {
        if(L == R) {
            tree[treeIndex] = value;
            return;
        }
        if(element <= (L+R)/2)
            update(treeIndex*2, L, (L+R)/2, element, value);
        else if(element >= (L+R)/2 + 1)
            update(treeIndex*2 + 1, (L+R)/2 + 1, R, element, value);
        tree[treeIndex] = tree[treeIndex*2]*tree[treeIndex*2 + 1];
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
        return left*right;
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
        tree[treeIndex] = tree[treeIndex*2]*tree[treeIndex*2 + 1];
    }
public:
    SegmentTree(int values[], int N) : N(N) {
        tree.clear();
        tree.assign(2*(1<<(int(log(N)/log(2))+1)), 0);
        initialize(1, 0, N-1, 0, N-1, values);
    }
    void update(int i, int k) { update(1, 0, N-1, i, k); }
    int query(int from, int to) { return query(1, 0, N-1, from, to); }
};

int main() {
    int N, K;
    while(cin >> N >> K) {
        int arr[N];
        FOR(i, 0, N) {
            cin >> arr[i];
            if(arr[i]) arr[i] /= abs(arr[i]);
        }

        SegmentTree st(arr, N);

        FOR(l, 0, K) {
            char type;
            cin >> type;
            int i, j;
            cin >> i >> j;
            if(type == 'C') {
                i--;
                st.update(i, j?j/abs(j):j);
            } else {
                i--, j--;
                int k = st.query(i, j);
                if(k>0)
                    cout << '+';
                else if(k<0)
                    cout << '-';
                else
                    cout << 0;
            }
        }
        cout << endl;
    }
}