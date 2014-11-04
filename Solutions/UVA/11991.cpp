

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
#include <unordered_map>
#include <vector>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;


int main() {
	int n, m;
	
	while(cin >> n >> m) {
		//vvi occ(1000001, vi());
		unordered_map<int, vi> occ;
		
		FOR(i, 0, n) {
			int x; cin >> x;
			occ[x].push_back(i);
		}
		FOR(i, 0, m) {
			int k, v;
			cin >> k >> v;
			
			if((k - 1) < occ[v].size()) {
				cout << (1 + occ[v][k - 1]) << endl;
			} else cout << 0 << endl;;
		}
	}
}
