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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

int conf[2001][2001], best[2001];

int main() {
	//char tbl[1000];
	
	int c; cin >> c;
	while(c--) {
		int t,h,f;
		cin >> t >> h >> f;
		memset(conf, 0, sizeof conf);
		
		FOR(i, 0, t) {
			int a; cin >> a;
			
			FOR(x, 0, a) {
				int hx; cin >> hx;
				
				conf[i][h - hx]++;
			}
		}
		
		FOR(drop, 0, h + 1) {
			FOR(i, 0, t) {
				int plus = 0;
				if(drop)
					plus = max(plus, conf[i][drop - 1]);
				if(drop - f >= 0)
					plus = max(plus, best[drop - f]);
				
				conf[i][drop] += plus;
				best[drop] = max(best[drop], conf[i][drop]); 
			}
		}
		
		cout << best[h] << endl;
	}
}
