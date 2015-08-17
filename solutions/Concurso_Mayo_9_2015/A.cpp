/*
3
1 2 3
1 2 3
1 2 3
4
10 28 12 3
8 25 11 13
15 21 32 10
10 9 8 7
0
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
#define FOR(i, a, b) for(int i=a; i<b; i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

mint arr[1000][1000];
int ans[1000][1000];

mint main() {
	int N;
	while(scanf("%lld", &N) != EOF && N) {
		FOR(i, 0, N)
			FOR(j, 0, N)
				scanf("%d", &arr[i][j]);
		for(int i = N-1; i >= 0; i--) {
			for(int j = 0; j < N-i; j++) {
				int x = N-1-j, y = i+j;
				arr[x][y] += max(x+1< N ? arr[x+1][y] : 0, y+1 < N ? arr[x][y+1] : 0);
				// cout << N-1-j << " " << i+j << endl;
			}
		}

		for(int i = N-2; i >=0; i--) {
			for(int j = 0; j <= i; j++) {
				int x = i-j, y = j;
				arr[x][y] += max(x+1< N ? arr[x+1][y] : 0, y+1 < N ? arr[x][y+1] : 0);
				// cout << i-j << " " << j << endl;
			}
		}
		cout << arr[0][0] << endl;
	}
}