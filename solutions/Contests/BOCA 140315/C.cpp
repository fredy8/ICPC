/*
10 3
1 4 8
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

int pts[110];

mint main() {
	int N, P;
	cin >> N >> P;
	vi ps(P, 0);
	FOR(i, 0, P) {
		int p;
		cin >> p;
		ps[i] = p;
		pts[p] = 1;
		FOR(j, 0, i) {
			pts[p-ps[j]] = 1;
		}
	}

	FOR(i, 0, P)
		pts[N-ps[i]] = 1;
	pts[N] = 1;

	bool first = true;
	FOR(i, 1, 110) {
		if (pts[i]) {
			if (!first)
				cout << " ";
			cout << i;
			first = false;
		}
	}

	cout << endl;
}