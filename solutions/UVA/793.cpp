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

vi parent, _rank;

int find(int n) {
  if (n == parent[n]) return n;
  return parent[n] = find(parent[n]);
}

void _union(int a, int b) {
  int pa = find(a), pb = find(b);
  if (pa == pb) {
    return;
  }

  if (_rank[pa] > _rank[pb])
    parent[pb] = pa;
  else
    parent[pa] = pb;

  if (_rank[pa] == _rank[pb])
    _rank[pb]++;
}

int main() { _
  int TC;
  cin >> TC;
  int N;
  string aux;
  bool first = true;
  while(TC--) {
    if (!first) cout << endl;
    first = false;
    cin >> N;
    getline(cin, aux);
    parent.assign(N, 0), _rank.assign(N, 0);
    FOR(i, 0, N) parent[i] = i;

    int ans[2] = {0, 0};
    string line;
    while(getline(cin, line)) {
      if (line == "") {
        break;
      }

      char type;
      int n1, n2;
      istringstream iss(line);
      iss >> type >> n1 >> n2;
      n1--, n2--;
      if (type == 'c') {
        _union(n1, n2);
      } else {
        ans[find(n1) != find(n2)]++;
      }
    }

    cout << ans[0] << "," << ans[1] << endl;
  }
}