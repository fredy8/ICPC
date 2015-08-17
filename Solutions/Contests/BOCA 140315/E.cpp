/*
25.0 100.0
190.0 57.5
4
125.0 67.5
75.0 125.0
45.0 72.5
185.0 102.5
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
#include <list>
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
#define MAX_V 400

double dista[103][103];
int nextt[103][103];

bool portal[103][103];

#define SQ(x) ((x)*(x))
#define DIST(a, b) (sqrt(SQ((b).first - (a).first) + SQ((b).second - (a).second)))


void print_path(int u, int v) {
  cout << u << endl;
  while(u != v) {
    int old_u = u;
    u = nextt[u][v];
    cout << "xx" << old_u << "," << u << endl; 
  cout << u << (portal[old_u][u] ? " portal " : " ") << dista[old_u][u] <<endl;


  }
}

mint main() {
  int n;
  double x,y;
  vector<pair<double, double> > points;

  cin >> x >> y;
  points.pb(mp(x,y));
  cin >> x >> y;
  points.pb(mp(x,y));

  cin >> n;
  FOR(i,0,n) {
    cin >> x >> y;
    points.pb(mp(x,y));
  }

  FOR(u, 0, points.size()) {
  
    FOR(v, 0, points.size()) {
      if(u == v) 
        dista[u][v] = dista[v][u] = 0;
      else {
        double dist = DIST(points[u], points[v]) ;
        double walking_time = dist/5;
        double portal_time = (u >= 2) ? abs((50 - dist)/5) + 2 : INF;
        dista[u][v] = min(portal_time, walking_time);
        nextt[u][v] = v;
        if(portal_time < walking_time) portal[u][v]  = true;
        cout << (dista[u][v]) <<(portal[u][v] ? "p" : " ") << " ";
        
      }

    }
    cout << endl;
  }


	FOR(k, 0, n)
		FOR(i, 0, n)
			FOR(j, 0, n)
 {
				//dista[j][k] = miin(dista[j][k], dista[j][i] + dista[i][k]);
				if(dista[i][k] + dista[k][j] < dista[i][j]) {
          dista[i][j] =   dista[i][k] + dista[k][j];
          nextt[i][j] = nextt[i][k];
        };
      }
 cout << "dista " << endl;
  FOR(u, 0, points.size()) {
    FOR(v, 0, points.size()) {
      cout << DIST(points[u], points[v]) << " ";
    }
    cout << endl;
  }
 cout << "porta " << endl;
  FOR(u, 0, points.size()) {
    FOR(v, 0, points.size()) {
      cout << dista[u][v] << " ";
    }
    cout << endl;
  }

  
  cout << dista[0][1] << endl;

cout << "::::::"
<< endl;

print_path(0,1);
}