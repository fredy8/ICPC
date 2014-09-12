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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int wind[11][1001];
int cost[11][1001];

int main() {
	int n; cin >> n;
	
	while(n--) {
		int x; cin >> x; x /= 100;
		
		for(int i = 9; i >= 0; i--) {
			FOR(j, 0, x) {
				cin >> wind[i][j];
			}
		}
		
		FOR(i, 0, 10) cost[i][0] = INF;
		cost[0][0] = 0;
		
		FOR(j, 1, x+1) {
			FOR(i, 0, 10) {
				cost[i][j] = cost[i][j-1] + 30 - wind[i][j-1];
				
				
				if(i < 9)
					cost[i][j] 
						= min(cost[i][j], 
						cost[i + 1][j-1] + 20 - wind[i + 1][j-1]);
				
				if(i > 0)
					cost[i][j] 
						= min(cost[i][j], 
						cost[i - 1][j-1] + 60 - wind[i - 1][j-1]);
				else if(j < x) { // i == 0, j < x
					cost[i][j] = INF; // no tocar el suelo hasta aterrizar
				}
			}
		}
		
		FOR(i, 0, 9) 
		{ FOR(j, 0, x+1) cout << cost[i][j] << " "; cout <<endl;}
		
		cout << cost[0][x] << endl;
		if(n) cout << endl;
	}
}

/*
 * 
3755PR/1E/9V6
5377BR/12/9WU
5707BA/12/9V6
5327BA/1E/9V6
7337BA/1E/9V6
7137BA/11/9V6

*/
