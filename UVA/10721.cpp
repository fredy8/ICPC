
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

ll BC[51][51][51];
ll bcbc(int n, int k, int m) ;
ll bc(int n, int k, int m) {
	if(k == n && k == 0) {
		return 1;
	} else if(/*k > n || k * m < n ||*/ k == 0 || n == 0) {
		
		return 0;
	} else if(k == n || (k == 1 && m >= n)) {
		
	//cout << "count "
	//	<< n << " "
	//	<< k << " "
	//	<< m << " = " << 1 << endl;
		
		return 1;
	}
	
	ll count = 0;
	
	for(ll i = 1; i <= m && i <= n; i++) {
		count += bcbc(n - i, k - 1, m);
	}
	
	
	//cout << "count "
	//	<< n << " "
	//	<< k << " "
	//	<< m << " = " << count << endl;
	
	return count;
}

ll bcbc(int n, int k, int m) {
	return BC[n][k][m] == -1 ? (BC[n][k][m] = bc(n, k, m))
		: BC[n][k][m];
}

int main() {
	ll n, k, m;
	memset(BC, -1, sizeof BC);
	
	while(cin >> n >> k >> m) {
		cout << (unsigned long long)bcbc(n, k, m) << endl;
	}
	
}
