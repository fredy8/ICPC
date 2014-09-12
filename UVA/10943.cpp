
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

int mways[101][101];

int ways(int n, int k) {
	if(mways[n][k])
		return mways[n][k];
	
	if(k == 1)
		return mways[n][k] = 1;
	
	int w = 0;
	
	for(int i = 0; i <= n; i++) {
		w += ways(i, k - 1);
		w %= 1000000;
	}
	
	return mways[n][k] = w;
}

int main() {
	int n, k;
	
	while(cin >> n >> k, n || k) {
		cout << ways(n, k) << endl;
	}
	
}
// a b a b a3
