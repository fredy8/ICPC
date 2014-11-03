/*
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
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int i, j, TC, xsize, ysize, n;
int x[11], y[11];
ii memo[11][1 << 11]; 
int dist[11][11];

ii tsp(int pos, int bitmask) { 

  if (bitmask == (1 << n) - 1)
    return memo[pos][bitmask] = ii(dist[pos][0], 0); 
  if (memo[pos][bitmask].first != -1)
    return memo[pos][bitmask];

  ii ans = ii(INF, -15);
  int ndis;
  for (int nxt = 0; nxt < n; nxt++) { // O(n) here
	//  if(nxt != pos && nxt == 6) cout << "yes " << (bitmask | (1 << nxt)) << endl;
    if (nxt != pos && !(bitmask & (1 << nxt))) 
      ans = min(ans, ii(dist[pos][nxt] + tsp(nxt, bitmask | (1 << nxt)).first, nxt)); 
  }
  //cout << pos << ":     " << bitmask<<"       ?"<< ans.first << endl;
  assert(ans.first < INF);
  return memo[pos][bitmask] = ans;
}

mint main() {
	
}




int main() {
	int t; cin >> t;
	while(t--) {
		int xx,yy;
		cin >> xx >> yy;
		
		cin >> x[0] >> y[0];
		
		cin >> n; n++;
		FOR(j, 0, n)  FOR(i, 0, 1 << n) memo[j][i] = ii(-1,-1);
		
		FOR(i, 0, n) dist[0][i] = dist[i][0] = dist[i][i] = 0;
		FOR(i, 1, n) {
			cin >> x[i] >> y[i];
			
			
			FOR(j, 0, i) {
				dist[i][j] = dist[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
			}
		}
		
		cout << "The shortest path has length " << tsp(0,1).first << endl;
	}
}
