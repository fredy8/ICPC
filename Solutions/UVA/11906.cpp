/*
2
3 3 2 1
0
4 4 1 2
2
3 3
1 1
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef long long ll;


int main() {
	int TC;
	cin >> TC;
	FOR(tc, 1, TC+1) {
		int R, C, M, N;
		cin >> R >> C >> M >> N;

		int grid[100][100] = {0};

		int W;
		cin >> W;
		FOR(i, 0, W) {
			int a, b;
			cin >> a >> b;
			grid[a][b] = 1;
		}

		ii *moves;

		ii moves1[] = {ii(M, N), ii(N, M), ii(-M, N), ii(N, -M), ii(M, -N), ii(-N, M), ii(-M, -N), ii(-N, -M)};
		ii moves2[] = {ii(0, N), ii(N, 0), ii(-N, 0), ii(0, -N)};
		ii moves3[] = {ii(0, M), ii(M, 0), ii(-M, 0), ii(0, -M)};
		ii moves4[] = {ii(0, 0)};
		if(M == 0) {
			moves = moves2;
			if(N == 0)
				moves = moves4;
		} else if(N == 0) {
			moves = moves3;
		} else
			moves = moves1;

		grid[0][0] = 2;

		queue<ii> q;
		q.push(ii());
		while(!q.empty()) {
			ii current = q.front(); q.pop();
			FOR(i, 0, 8) {
				ii next = ii(moves[i].first + current.first, moves[i].second + current.second);
				if(next.first >= 0 && next.first < R && next.second >= 0 && next.second < C && grid[next.first][next.second] == 0) {
					grid[next.first][next.second] = 2;
					q.push(next);
				}
			}
		}

		int even = 0, odd = 0;

		FOR(i, 0, R) {
			FOR(j, 0, C) {
				int reachableFrom = 0;
				if(grid[i][j] == 2) {
					FOR(k, 0, 8) {
						if(M == N && k%2) {
							continue;
						}
						ii next = ii(moves[k].first + i, moves[k].second + j);
						if(next.first >= 0 && next.first < R && next.second >= 0 && next.second < C && grid[next.first][next.second] == 2) {
							reachableFrom++;
						}
					}
					(reachableFrom%2 ? odd:even)++;
				}
			}
		}

		cout << "Case " << tc << ": " << even << " " << odd << endl;
	}
}