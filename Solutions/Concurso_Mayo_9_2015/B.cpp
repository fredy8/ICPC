/*
3
5
2 3 4 5
3
1 2
10
1 2 3 4 6 7 8 9 10
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

mint main() {
	int T;
	scanf("%lld", &T);
	while (T--) {
		int N, m, sum = 0;
		scanf("%lld", &N);
		FOR(i, 0, N-1) {
			scanf("%lld", &m);
			sum += m;
		}
		printf("%lld\n", N*(N+1)/2 - sum);
	}
}