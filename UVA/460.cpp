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
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;


/*
1

0 20 100 120
80 0 500 60
*/

int main() {
	int t; cin >> t;
	
	while(t--) {
		int x,y,z,w, x1,y1,z1,w1;
		
		cin >> x >> y >> z >> w
			>> x1 >> y1 >> z1 >> w1;
			
		// int difx = z - x, difx2 = w - y;
		// int dify = 
		
		if(max(z, z1) - min(x, x1) < (z - x) + (z1 - x1)
			&& max(w, w1) - min(y, y1) < (w - y) + (w1 - y1)) {
			
			cout << max(x, x1) << " "
				 << max(y, y1) << " "
				 << min(z, z1) << " "
				 << min(w, w1) << endl;
		} else cout << "No Overlap" << endl;
		
		if(t) cout << endl;
	}
}
