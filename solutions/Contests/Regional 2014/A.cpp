/*
1 0 0 1 0
1 0 1 1 0
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std;
typedef long long ll; typedef pair<int, int> ii;
typedef vector<int> vi; typedef vector<ii> vii;
typedef vector<vi> vvi;

bool valid (vi x, vi y) {
	FOR(i, 0, 5)
		if (x[i] == y[i]) return false;
	return true;
}

mint main() {
	vi X(5,0), Y(5,0);
	FOR(i, 0, 5) cin >> X[i];
	FOR(i, 0, 5) cin >> Y[i];
	cout << (valid(X,Y) ? "Y" : "N") << endl;
}
