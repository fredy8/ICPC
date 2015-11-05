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
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Node {
  ii L, R, M;
};

Node combine(Node &l, Node &r) {
  Node res;
  res.L = ii(l.L.first, l.L.second + (r.L.first == l.L.first ? r.L.second : 0));
  res.R = ii(r.R.first, r.R.second + (l.R.first == r.R.first ? l.R.second : 0));
  res.M = l.M.second > r.M.second ? l.M : r.M;
  if (l.R.first == r.L.first && l.R.second + r.L.second > res.M.second)
    res.M = ii(l.R.first, l.R.second + r.L.second);
  return res;
}

int main() { _
  int n, q;
  while(cin >> n && n) {
    cin >> q;
    vector<Node> tree(2*n);
    FOR(i, 0, n) {
      cin >> tree[n+i].M.first;
      tree[n+i].L.first = tree[n+i].R.first = tree[n+i].M.first;
      tree[n+i].L.second = tree[n+i].R.second = tree[n+i].M.second = 1;
    }
    for(int i = n-1; i > 0; --i)
      tree[i] = combine(tree[i<<1], tree[i<<1|1]);

    while(q--) {
      int from, to;
      cin >> from >> to;
      from--, to;
      if (from > to) swap(from, to);
      
      Node ansl, ansr;
      for(int l = n + from, r = n + to; l < r; l >>= 1, r >>= 1) {
        if (l&1) ansl = combine(ansl, tree[l++]);
        if (r&1) ansr = combine(tree[--r], ansr);
      }
      cout << combine(ansl, ansr).M.second << endl;
    }
  }
}