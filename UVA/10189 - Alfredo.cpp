/*
4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0
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



int main() {
	int R, C;
	int caseNum = 1;
	while(cin >> R >> C && R && C) {

		if(caseNum != 1)
			cout << endl;

		cout << "Field #" << caseNum++ << ":" << endl;

		string input[100];
		string output[100];

		FOR(i, 0, R) {
			cin >> input[i];
			output[i] = input[i];
		}

		ii moves[] = {ii(-1, -1), ii(-1, 0), ii(-1, 1), ii(0, -1), ii(0, 1), ii(1, -1), ii(1, 0), ii(1, 1)};

		FOR(i, 0, R) {
			FOR(j, 0, C) {
				int count = 0;
				FOR(k, 0, 8) {
					ii next = ii(i + moves[k].first, j + moves[k].second);
					count += next.first >= 0 && next.second >= 0 && next.first < R && next.second < C && input[next.first][next.second] == '*';
				}
				if(input[i][j] == '*')
					output[i][j] = '*';
				else
					output[i][j] = count + '0';
			}
			cout << output[i] << endl;
		}

	}
}