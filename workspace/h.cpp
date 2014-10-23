/*
5
4 5 2 3 1
3
1 2 3
9
9 4 2 7 8 3 5 6 1
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

mint main() {
	int N;
	while(cin >> N) {
		vi sets;
		FOR(i, 0, N) {
			int n; cin >> n;
			vi::iterator it = lower_bound(sets.begin(), sets.end(), n, greater<int>());
			if(it == sets.end()) sets.pb(n);
			else *it = n;
		}
		cout << sets.size() << endl;
	}
}
