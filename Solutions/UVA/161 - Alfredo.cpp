/*
19 20   0
11 13 17 23 29 31 39 41 43 47 53 59 61 67 71 0
0 0
#
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

#define GREEN 0
#define ORANGE 1
#define RED 2

int solve(vi cycles) {
	vi states(cycles.size(), GREEN);
	priority_queue<ii, vii, greater<ii> > q;
	FOR(i, 0, cycles.size())
		q.push(ii(cycles[i] - 5, i));

	while(!q.empty()) {
		ii front = q.top(); q.pop();
		int index = front.second;
		int currentTime = front.first;

		if(currentTime > 5*60*60) {
			return -1;
		}

		states[index] = (states[index] + 1) % 3;

		if(!q.size() || q.top().first != currentTime) {
			bool allGreen = true;
			FORC(states, it)
				if(*it != GREEN)
					allGreen = false;

			if(allGreen)
				return currentTime;
		}

		int nextEvent[] = { cycles[index] - 5, 5, cycles[index] };
		q.push(ii(currentTime + nextEvent[states[index]], index));
	}

	return -1;
}

void print(int num) {
	if(num == -1) {
		cout << "Signals fail to synchronise in 5 hours" << endl;
		return;
	}

	int hrs = num / (60*60);
	int mins = (num / 60) % 60;
	int secs = num % 60;

	printf("%02d:%02d:%02d\n", hrs, mins, secs);
}

int main() {
	vi cycles;
	do {
		int num;
		cycles.clear();
		while(cin >> num && num)
			cycles.pb(num);

		if(cycles.size())
			print(solve(cycles));

	} while(cycles.size());
}