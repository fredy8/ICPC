
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
#include <cassert>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

ll sum[21][21][21];

int main() {
	int t, a, b, c;
	cin >> t;
	
	while(t--) {
		cin >> a >> b >> c;
		memset(sum, 0, sizeof sum); // ?
		
		FOR(i, 1, a + 1) {
			FOR(j, 1, b + 1) {
				FOR(k, 1, c + 1) {
					cout << i << "," << j << "," << k << endl;
					cin >> sum[i][j][k];
					sum[i][j][k] = sum[i][j][k]
						+ sum[i - 1][j][k]
						+ sum[i][j - 1][k]
						+ sum[i][j][k - 1]
						
						- sum[i - 1][j - 1][k]
						- sum[i][j - 1][k - 1]
						- sum[i - 1][j][k - 1]
						+ sum[i - 1][j - 1][k - 1];
				}
			}
		}
		
		ll maxs = sum[1][1][1];
		
		FOR(i, 0, a) {
			FOR(j, 0, b) {
				FOR(k, 0, c) {
					FOR(x, i, a + 1) {
						FOR(y, j, b + 1) {
							FOR(z, k, c + 1) {
								ll curr = sum[x][y][z]
									- sum[x][y][k]
									- sum[x][j][z]
									- sum[i][y][z]
									+ sum[x][j][k]
									+ sum[i][j][z]
									+ sum[i][y][k]
									- sum[i][j][k];
								maxs = max(maxs, curr);
							}
						}
					}
				}
			}
		}
		
		cout << maxs << endl;
	}
}
// a b a b a3
