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

vi LongestIncreasingSubsequence(vi v) {
	if(v.size() == 0) return vi();
    vi lis(v.size());
    
    lis[0] = 1;
    
    FOR(i, 0, v.size()) {
		lis[i] = 1;
		FOR(j, 0, i) {
			if(v[i] > v [j]) lis[i] = max(lis[i], 1 + lis[j]);
		}
	}
	return lis;
}

vi LongestDecreasingSubsequence(vi v) {
	if(v.size() == 0) return vi();
    vi lis(v.size());
    
    lis[0] = 1;
    
    FOR(i, 0, v.size()) {
		lis[i] = 1;
		FOR(j, 0, i) {
			if(v[i] < v [j]) lis[i] = max(lis[i], 1 + lis[j]);
		}
	}
	return lis;
}

int main() {
	int t; cin >> t;
	
	while(t--) {
		int n; cin >> n;
		
		vi cars;
		while(n--) {int x; cin >> x; cars.pb(x);}
		
		reverse(cars.begin(), cars.end());
		vi lis = LongestIncreasingSubsequence(cars), 
			lds = LongestDecreasingSubsequence(cars);
		
		int ans = 0;
		FOR(i, 0, cars.size()) {
			ans = max(ans, lis[i] + lds[i] - 1);
		}
		cout << ans << endl;
	}
}
