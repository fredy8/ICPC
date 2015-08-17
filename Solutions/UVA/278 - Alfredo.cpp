/*
2
r 6 7
k 8 8
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

int R, C;
int solve(int col, int horizontal, int diagDown, int diagUp) {
	if(col == C)
		return 0;
	int MAX = solve(col+1, horizontal, diagDown<<1, diagUp>>1);
	FOR(i, 0, R)
		if((~(horizontal | diagDown | diagUp)) & (1<<i))
			MAX = max(1+solve(col+1, horizontal | (1<<i), (diagDown | (1<<i)) << 1, (diagUp | (1<<i)) >> 1), MAX);
	return MAX;
}

int main() {
	int N;
	cin >> N;
	while(N--) {
		char type;
		cin >> type >> R >> C;
		if(type == 'r')
			cout << min(R, C) << endl;
		else if(type == 'K')
			cout << ((R+1)/2)*((C+1)/2) << endl;
		else if(type == 'Q')
			cout << solve(0, 0, 0, 0) << endl;
		else if(type == 'k')
			cout << (max(R, C)/2 + (max(R, C)%4 != 0))*min(R, C) << endl;
	}
}