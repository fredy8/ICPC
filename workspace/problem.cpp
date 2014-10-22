/*
3 6 
2 1 2 4 0 4 
4 3 
2 0 3 2 0 2 
8 8
7 8 5 6 3 4
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

typedef unsigned long long ull;

int R, C;
ii CP[5];

int distanceTo[8][8];

ii moves[] = {ii(-1, 0), ii(0, -1), ii(0, 1), ii(1, 0)};

bool good(ii pos) {
	return pos.first >= 0 && pos.second >= 0 && pos.first < R && pos.second < C;
}

#define INDEX(r, c) (1ull<<((r)*C+(c)))

void bfs(ii initial, ull visited) {
	FOR(i, 0, R) FOR(j, 0, C) distanceTo[i][j] = -1;
	distanceTo[initial.first][initial.second] = 0;
	queue<ii> q; q.push(initial);
	while(!q.empty()) {
		ii current = q.front(); q.pop();
		FOR(i, 0, 4) {
			ii next(current.first + moves[i].first, current.second + moves[i].second);
			if(good(next) && !(visited & INDEX(next.first, next.second)) && distanceTo[next.first][next.second] == -1) {
				q.push(next);
				distanceTo[next.first][next.second] = distanceTo[current.first][current.second] + 1;
			}
		}
	}
}

#define TARGET(i) ((i) ? (int(R*C/4.0*(i)+.0001)) : 1)

bool realGood(ii pos, ull visited, int reverse) {
	if(!good(pos))
		return false;
	if(visited & INDEX(pos.first, pos.second))
		return false;

	visited |= INDEX(pos.first, pos.second);

	int steps = __builtin_popcount(visited);
	bfs(pos, visited);
	FOR(i, 0, R) FOR(j, 0, C)
		if(!(visited & INDEX(i, j)) && distanceTo[i][j] == -1) {
			return false;
		}
	
	FOR(i, 0, 5) {
		int tg = TARGET(i);
		if(reverse)
			tg = R*C - tg + 1;
		if(pos == CP[i] && steps != tg) {
			return false;
		}
		if(steps <= tg) {
			int dist = distanceTo[CP[i].first][CP[i].second];
			if(dist + steps > tg) {
				return false;
			}
		}
	}

	return true;
}

map<pair<ii, ull>, int> waysToGetHere;
int ans;
void solve(ii pos, ull visited, bool reverse) {
	//cout << pos.first << ", " << pos.second << "   " << bitset<64>(visited) << " : " << waysToGetHere[mp(pos, visited)] << endl;

	int steps = __builtin_popcount(visited);
	if(steps == R*C/2 + ((R*C)%2?1:reverse)) {
		ans += waysToGetHere[mp(pos, visited)] * waysToGetHere[mp(pos, (~visited & ((1ull << (R*C))-1)) | INDEX(pos.first, pos.second))];
		return;
	}

	vi goodNeighs;
	int bestNeigh;
	int bestCt = 0;
	FOR(i, 0, 4) {
		ii next(pos.first + moves[i].first, pos.second + moves[i].second);
		if(realGood(next, visited, reverse)) {
			int neighs = 0;
			FOR(j, 0, 4) {
				ii nextnext(next.first + moves[i].first, next.second + moves[i].second);
				if(neighs <= 1 && realGood(nextnext, visited | INDEX(next.first, next.second), reverse))
					neighs++;
			}
			if(neighs == 1) {
				bestNeigh = i;
				bestCt++;
			}
			goodNeighs.pb(i);
		}
	}

	if(bestCt > 1) {
		return;
	}

	if(bestCt == 1) {
		goodNeighs.clear();
		goodNeighs.pb(bestNeigh);
	}

	FORC(goodNeighs, it) {
		ii next(pos.first + moves[*it].first, pos.second + moves[*it].second);
		waysToGetHere[mp(next, visited | INDEX(next.first, next.second))] += waysToGetHere[mp(pos, visited)];
		solve(next, visited | INDEX(next.first, next.second), reverse);
	}
}

mint main() {
	int tc = 1;
	while(cin >> R >> C && R && C) {
		ans = 0;
		cout << "Case " << tc++ << ": ";
		cin >> CP[1].first >> CP[1].second;
		cin >> CP[2].first >> CP[2].second;
		cin >> CP[3].first >> CP[3].second;
		CP[4] = ii(0, 1);
		CP[0] = ii(0, 0);
		
		waysToGetHere[mp(ii(0, 0), 1)] = 1;
		solve(ii(0, 0), 1, false);
		waysToGetHere[mp(ii(0, 1), 2)] = 1;
		solve(ii(0, 1), 2, true);
		cout << ans << endl;
	}
}
