/*
1 2 3 4 5 6 7 8
1 1 1 1 1 1 1 1
1 3 5 7 2 4 6 8
4 6 8 2 7 1 3 5
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

struct state {
	int index, horizontal, diagUp, diagDown;
	int invalidPositions() {
		return horizontal | diagUp | diagDown;
	}
};

vi initialPos;

void printBin(int N) {
    bitset<8> b(N);
    cout << b << endl;
}

int solve(int index, int horizontal, int diagUp, int diagDown) {
	if(index == 8)
		return 0;

	int MIN = INF;
	FOR(i, 0, 8) {
		if(~(horizontal | diagUp | diagDown) & (1<<i)) {
			MIN = min(MIN, (i != initialPos[index]) + solve(index+1, horizontal | (1<<i), (diagUp | (1<<i))<<1, (diagDown | (1<<i))>>1));
		}
	}

	return MIN;
}

int main() {
	int caseNum = 1;
	while(true) {
		initialPos.clear();
		FOR(i, 0, 8) {
			int p;
			if(!(cin >> p)) {
				return 0;
			}
			initialPos.pb(p-1);
		}

		cout << "Case " << caseNum++ << ": ";

		cout << solve(0, 0, 0, 0) << endl;
	}
}