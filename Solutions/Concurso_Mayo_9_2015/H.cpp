/*
5
1 -1 1 -1 1
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
	int N, n, sum = 0, t = 0;
	map<int, int> mapa;
	cin >> N;
	mapa[0] = 1;
	FOR(i, 0, N) {
		cin >> n;
		sum += n;
		if (mapa.find(sum) != mapa.end()) {
			t += mapa[sum];
			mapa[sum]++;
		} else {
			mapa[sum] = 1;
		}
	}
	cout << t << endl;
}