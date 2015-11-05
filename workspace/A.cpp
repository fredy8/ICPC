#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define RFORC(cont, it) for(decltype((cont).rbegin()) it=(cont).rbegin(); it!=(cont).rend(); it++)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct SparseTable {
  vi A; vvi M;
  ll log2(ll n) { ll i=0; while(n >>= 1) i++; return i; }
  SparseTable(vi arr) {
    ll N = arr.size();
    A.assign(N, 0);
    M.assign(N, vi(log2(N)+1));
    ll i, j;
    for(i=0; i<N; i++)
      M[i][0] = i, A[i] = arr[i];

    for(j=1; 1<<j <= N; j++)
      for(i=0; i + (1<<j) - 1 < N; i++)
        if(A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }
  ll query(ll i, ll j) {
    if(i > j) swap(i, j);
    ll k = log2(j-i+1);
    if(A[M[i][k]] < A[M[j-(1 << k)+1][k]])
      return M[i][k];
    return M[j-(1 << k)+1][k];
  }
};

struct Edge {
  ll to, weight;
  Edge(ll to, ll weight = 1) : to(to), weight(weight) {}
};
struct Graph {
  ll V; bool undirected;
  vector<vector<Edge> > edges;
  Graph(ll v, bool undirected) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
  void connect(ll from, Edge edge) {
    edges[from].pb(edge);
    if(undirected) {
      ll aux = edge.to;
      edge.to = from;
      edges[aux].pb(edge);
    }
  }
};

struct LCA {
  vi order, height, index;
  SparseTable *st;
  LCA(Graph &g, ll root) {
    index.assign(g.V, -1);
    dfs(g, root, 0, index);
    st = new SparseTable(height);
  }
  ~LCA() { delete st; }
  void dfs(Graph &g, ll cv, ll h, vi &index) {
    index[cv] = order.size();
    order.pb(cv), height.pb(h);
    FORC(g.edges[cv], edge)
      if(index[edge->to] == -1) {
        dfs(g, edge->to, height.back() + edge->weight, index);
        order.pb(cv), height.pb(h);
      }
  }
  ll query(ll i, ll j) { return order[st->query(index[i], index[j])]; }
  ll distance(ll i, ll j) { return height[index[i]] + height[index[j]] - 2*(height[index[query(i, j)]]); }
};

#define e18 1000000000000000000ll

ii orderii(ii a) { return ii(min(a.first, a.second), max(a.first, a.second)); }

inline ll multiply2(ll a, ll b) {
  double logsum = log10(a) + log10(b);
  if (logsum >= 18)
    return e18 + (logsum != 18);
  return a*b;
}

inline void multiply(ll &a, ll b) { a = multiply2(a, b); }

struct SegmentTree {
  vi tree;
  ll N;
  SegmentTree(vi &values) {
    tree.assign(values.size()*2, 0);
    N = values.size();
    FOR(i, 0, N)
      tree[i + N] = values[i];
    for(ll i = N - 1; i; i--)
      tree[i] = multiply2(tree[i<<1], tree[i<<1|1]);
  }
  void set(ll index, ll value) {
    tree[index + N] = value;
    for(ll i = (index + N)>>1; i; i >>= 1)
      tree[i] = multiply2(tree[i<<1], tree[i<<1|1]);
  }
  ll query(ll from, ll to) {
    ll ans = 1;
    for(ll l = N + from, r = N + to; l < r; l >>= 1, r >>= 1) {
      if (l&1) multiply(ans, tree[l++]);
      if (r&1) multiply(ans, tree[--r]);
    }
    return ans;
  }
};

map<ii, ll> edgeToNode;
map<ll, ii> edgeIndexToValue;
vector<vi> lists;
vi values, listIndex, posIndex, parent, treeSizes;
vector<SegmentTree> sts;
LCA *lca;

struct HeavyLightDecomposition {
  HeavyLightDecomposition(Graph &g/*undirected connected acyclic*/) {
    lca = new LCA(g, 0);
    listIndex = posIndex = parent = treeSizes = vi(g.V, -1);
    getTreeSizes(g, 0);
    values.assign(g.V, 1);
    makeLists(g, 0, -1);
    FORC(lists, list) {
      vi v;
      FORC(*list, it) v.pb(values[*it]);
      sts.pb(SegmentTree(v));
    }
  }
  ~HeavyLightDecomposition() { delete lca; }
  ll getTreeSizes(Graph &g, ll cv) {
    treeSizes[cv] = 1;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv])
      parent[edge->to] = cv, treeSizes[cv] += getTreeSizes(g, edge->to);  
    return treeSizes[cv];
  }
  void makeLists(Graph &g, ll cv, ll listNum) {
    if(listNum == -1)
      listNum = lists.size(), lists.pb(vi());
    listIndex[cv] = listNum;
    posIndex[cv] = lists[listNum].size();
    lists[listNum].pb(cv);
    ll MAX = -1;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv]) {
      if(MAX == -1 || treeSizes[edge->to] > treeSizes[MAX]) MAX = edge->to;
    } else values[cv] = edge->weight, edgeToNode[orderii(ii(cv, edge->to))] = cv;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv])
      makeLists(g, edge->to, edge->to == MAX ? listNum : -1); 
  }
  ll query(ll from, ll to) {
    if (from == to) return 1;
    ll anc = lca->query(from, to), posLeft, posRight;
    ll result = multiply2(queryToAncestor(from, anc, posLeft), queryToAncestor(to, anc, posRight));
    if(posLeft < posRight) swap(posLeft, posRight);
    if (posRight != posIndex[anc])
      multiply(result, sts[listIndex[anc]].query(posIndex[anc]+1, posRight+1));
    if(posRight != posLeft)
      multiply(result, sts[listIndex[anc]].query(posRight+1, posLeft+1));
    return result;
  }
  ll queryToAncestor(ll from, ll anc, ll &posInAncestorList) {
    ll result = 1, left = from;
    while(listIndex[left] != listIndex[anc]) {
      multiply(result, sts[listIndex[left]].query(0, posIndex[left]+1));
      left = parent[lists[listIndex[left]][0]];
    }
    posInAncestorList = posIndex[left];
    return result;
  }
  void set(ll index, ll value) {
    sts[listIndex[index]].set(posIndex[index], value);
  }
};

int main() {_
  ll N, M;
  cin >> N >> M;

  Graph g(N, true);
  ll edgeI = 1;
  FOR(i, 0, N-1) {
    ll a, b, c;
    cin >> a >> b >> c;
    g.connect(a-1, Edge(b-1, c));
    edgeIndexToValue[edgeI++] = orderii(ii(a-1, b-1));
  }

  HeavyLightDecomposition hld(g);

  FOR(i, 0, M) {
    ll type;
    cin >> type;
    if (--type) {
      ll edgeIndex, val;
      cin >> edgeIndex >> val;
      ll edgeResponsible = edgeToNode[edgeIndexToValue[edgeIndex]];
      hld.set(edgeResponsible, val);
    } else {
      ll from, to, y;
      cin >> from >> to >> y;
      from--, to--;
      ll mult = hld.query(from, to);
      cout << y / mult << endl;
    }
  }
}