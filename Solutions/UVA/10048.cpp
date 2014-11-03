/*
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2
7 6 3
1 2 50
1 3 60
2 4 120
3 6 50
4 6 80
5 7 40
7 5
1 7
2 4
0 0 0
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
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct UnionFindDS {
    vi tree;
    UnionFindDS(int n) { FOR(i, 0, n) tree.push_back(i); }
    int root(int i) { return tree[i] == i ? i : tree[i] = root(tree[i]); }
    bool connected(int i, int j) {return root(i) == root(j);}
    void connect(int i, int j) { tree[root(i)] = tree[root(j)]; }
};

int *comparator;
bool compare(int a, int b) { return comparator[a] < comparator[b]; }
int kruskal(vii &edges, int weight[], int V, int a, int b) {
    vi order(edges.size());    
    UnionFindDS ds(V+1);
    comparator = weight;
    int maxEdge = 0;
    FOR(i, 0, order.size()) order[i] = i;
    sort(order.begin(), order.end(), compare);
    for(int i=0; i<int(edges.size()); i++)
        if(!ds.connected(edges[order[i]].first, edges[order[i]].second)) {
            ds.connect(edges[order[i]].first, edges[order[i]].second);
            maxEdge = max(maxEdge, weight[order[i]]);
            if(ds.connected(a, b))
                return maxEdge;
        }
    return -1;
}

int main() {
    int N, E, Q;
    bool first = true;
    int tc = 1;
    while(cin >> N >> E >> Q && N) {
        if(!first)
            cout << endl;
        first = false;
        vii edges;
        int weight[E];
        FOR(i, 0, E) {
            int from, to;
            cin >> from >> to >> weight[i];
            edges.pb(ii(from, to));
        }

        cout << "Case #" << tc++ << endl;
        FOR(i, 0, Q) {
            int from, to;
            cin >> from >> to;
            int ans = kruskal(edges, weight, N, from, to);
            if(ans == -1)
                cout << "no path" << endl;
            else
                cout << ans << endl;
        }
    }
}