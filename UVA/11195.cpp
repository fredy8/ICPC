/*
8
........
........
........
........
........
........
........
........
4
.*..
....
....
....
15
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
...............
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

int badSquares[15];
int N;

int solve(int row, int brow, int  bDiagUp, int bDiagDown) {
	if(row == N) {
		return 1;
	}

	int allowedPos = ~(brow | bDiagUp | bDiagDown | badSquares[row]) & ((1 << N)-1);

	int ans = 0;
	while(allowedPos) {
		int pos = allowedPos & -allowedPos;
		ans += solve(row+1, brow | pos, (bDiagUp | pos) >> 1, (bDiagDown | pos) << 1);
		allowedPos -= pos;
	}

	return ans;
}

mint main() {
	int tc = 1;
	while(cin >> N && N) {
		FOR(i, 0, N) {
			badSquares[i] = 0;
			string line;
			cin >> line;

			FORC(line, c) {
				badSquares[i] <<= 1;
				badSquares[i] += (*c == '*');
			}

		}

		cout << "Case " << tc++ << ": " <<  solve(0, 0, 0, 0) << endl;
	}
}
