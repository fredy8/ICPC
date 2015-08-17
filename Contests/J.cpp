/*
16 2
3
5
100 1
2
20 3
2
3
4
0 0
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

typedef vector<vector<double> > Matrix;
#define EPS 1E-7
#define CREATE(R, C) Matrix(R, vector<double>(C));

mint main() {
	ios_base::sync_with_stdio(false);
	int n, k, f;
	while (cin >> k >> n && n && k) {
		vector<bool> arr(k+1, false);
		//bool arr[260] = {false};
		FOR(i, 0, n) {
			cin >> f;
			for (int j = f; j <= k; j += f) {
				arr[j] = true;
			}
		}
		int t = 0;
		FOR(i, 1, k+1) {
			t += arr[i];
		}
		cout << t << endl;
	}

}