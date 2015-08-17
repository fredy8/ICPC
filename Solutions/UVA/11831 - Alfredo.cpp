/*
3 3 2
***
*N*
***
DE
4 4 5
...#
*#O.
*.*.
*.#.
FFEFF
10 10 20
....*.....
.......*..
.....*....
..*.#.....
...#N.*..*
...*......
..........
..........
..........
..........
FDFFFFFFEEFFFFFFEFDF
0 0 0
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
#define FOR(i, a, b) for(long long i=a; i<b; i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<int, pair<int, int> > point;

string grid[100];

int main() {
	int R, C, I;

	while(cin >> R >> C >> I && R) {

		ii pos;
		int orientation = 0;

		FOR(i, 0, R) {
			cin >> grid[i];
			FOR(j, 0, C) {
				char c = grid[i][j];

				if(string("NLSO").find(c) != -1) {
					orientation = string("NLSO").find(c);
					pos = ii(i, j);
				}
			}
		}

		ii moves[] = { ii(-1, 0), ii(0, 1), ii(1, 0), ii(0, -1) };

		int stickers = 0;

		string instructions;
		cin >> instructions;
		FORC(instructions, it) {
			char c = *it;
			if(c == 'D') {
				orientation = (orientation + 1)%4;
			} else if(c == 'E') {
				orientation = (orientation + 3)%4;
			} else if(c == 'F') {
				ii nextPos = ii(pos.first + moves[orientation].first, pos.second + moves[orientation].second);
				if(nextPos.first >= 0 && nextPos.first < R && nextPos.second >= 0 && nextPos.second < C && grid[nextPos.first][nextPos.second] != '#') {
					if(grid[nextPos.first][nextPos.second] == '*') {
						grid[nextPos.first][nextPos.second] = '.';
						stickers++;
					}
					pos = nextPos;
				}
			}

			//cout << c << ": ";
			//cout << pos.first << " " << pos.second << " " << orientation << endl;
		}


		cout << stickers << endl;
	}

}