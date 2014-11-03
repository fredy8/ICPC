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
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int main() {
	int t; 
	
	while(cin >> t, t) {
		int x,y,z,s;
		
		int xmax = -INF, ymax=-INF, zmax=-INF, 
		x1min=INF, y1min=INF, z1min=INF;
		
		while(t--) {
			cin >> x >> y >> z >> s;
			xmax = max(xmax, x);
			ymax = max(ymax, y);
			zmax = max(zmax, z);
			
			x1min = min(x1min, x + s);
			y1min = min(y1min, y + s);
			z1min = min(z1min, z + s);
		}
		
		if((x1min - xmax) <0 || (y1min - ymax)<0 || (z1min - zmax)<0)
			cout << "0"<< endl;
		else cout << ((x1min - xmax) * (y1min - ymax)* (z1min - zmax)) << endl;
	}
}
