/*
3
1 5
5 20
20 1
3
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<int, pair<int, int> > point;

vector<ii> matrices;
int ans[10][10];
int memo[10][10];

int solve(int from, int to) {
	if(memo[from][to] != -1)
		return memo[from][to];
	if(from == to) {
		return 0;
	}

	int MIN = INF;
	int indexOfMin = from;
    FOR(i, from, to) {
    	int cost = solve(from, i) + solve(i+1, to) + matrices[from].first * matrices[i].second * matrices[to].second;
        if(cost < MIN) {
        	indexOfMin = i;
        	MIN = cost;
        }
    }

    ans[from][to] = indexOfMin;
    return memo[from][to] = MIN;
}

template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }


string print(int from, int to) {
	if(from == to) {
		return "A" + toString(from+1);
	}
	return "(" + print(from, ans[from][to]) + " x " + print(ans[from][to]+1, to) + ")";
}

int main() {
	int N;
	int tc = 1;
	while(cin >> N && N) {
		cout << "Case " << tc++ << ": ";
		matrices.clear();
		FOR(i, 0, 10)
			FOR(j, 0, 10)
				ans[i][j] = memo[i][j] = -1;

		FOR(i, 0, N) {
			int r, c;
			cin >> r >> c;
			matrices.pb(ii(r, c));
		}

		solve(0, N-1);
		cout << print(0, N-1) << endl;
	}
}