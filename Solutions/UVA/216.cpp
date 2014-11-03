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
#include <cassert>
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef pair<double, int> di;

int i, j, TC, xsize, ysize, n;
double x[11], y[11];
di memo[11][1 << 11]; // Karel + max 10 beepers
double dist[11][11];

di tsp(int pos, int bitmask) { // bitmask stores the visited coordinates

  if (bitmask == (1 << n) - 1)
    return memo[pos][bitmask] = di(dist[pos][0], 0); // return trip to close the loop
  if (memo[pos][bitmask].first != -1)
    return memo[pos][bitmask];

  di ans = di(2000000000, -15);
  double ndis;
  for (int nxt = 0; nxt < n; nxt++) { // O(n) here
	//  if(nxt != pos && nxt == 6) cout << "yes " << (bitmask | (1 << nxt)) << endl;
    if (nxt != pos && !(bitmask & (1 << nxt))) // if coordinate nxt is not visited yet
      ans = min(ans, di(dist[pos][nxt] + tsp(nxt, bitmask | (1 << nxt)).first, nxt)); //di(ndis, nxt);
  }
  //cout << pos << ":     " << bitmask<<"       ?"<< ans.first << endl;
  
  return memo[pos][bitmask] = ans;
}

void printsol(int j, int bitmask) {
	if(bitmask != 1 << n - 1) {
		int pos = memo[j][bitmask].second;
		if(j && pos)cout << "Cable requirement to connect ("
			<< fixed << setprecision(0) << x[j]<<","<<y[j]
			<<") to ("<<x[pos]<<","<<y[pos]<<") is " 
			<< fixed << setprecision(2) << dist[j][pos] <<" feet." << endl;
		if(pos != -1)printsol(pos, bitmask | 1 << pos);
	}
}

int main() {
	int m; int tc = 0;
	while(cin >> m, m) {
		tc++;
		n = m + 1;
		FOR(j, 0, n)  FOR(i, 0, 1 << n) memo[j][i] = di(-1,-1);
		
		FOR(i, 0, n) dist[0][i] = dist [i][0] = dist[i][i] = 0;
		FOR(i, 1, n) {
			cin >> x[i] >> y[i];
			
			
			FOR(j, 1, i) {
				dist[i][j] = dist[j][i] = 16 + hypot(x[i] - x[j], y[i] - y[j]);
			}
		}
		
		di res = tsp(0,1);
		
		cout << "**********************************************************" <<endl;
		cout << "Network #" << tc << endl;
		
		printsol(0, 1);
		
		cout << "Number of feet of cable required is " 
		<< fixed << setprecision(2) <<res.first <<"."<< endl;
	}
}
