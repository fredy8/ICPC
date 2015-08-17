/*
3 6 
2 1 2 4 0 4 
4 3 
2 0 3 2 0 2 
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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

int visited[9][9];
char moves[9][9];
int r1,c1,r2,c2,r3,c3;
int m, n;

int id[65], jd[65];
ll ways;


int reachv[9][9];

int reach(int i, int j) {
	if(i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || reachv[i][j])
		return 0;
	
	reachv[i][j] = true;
	return 1 + reach(i-1,j) + reach(i+1,j) + reach(i,j-1) + reach(i,j+1);
}

void solve(int i, int j, int depth) {
	if(i < 0 || i >= m || j < 0 || j >= n || visited[i][j]) return;
	
	//id[depth] = i;
	//jd[depth] = j;
	
	
	if(depth == m*n / 4 && (i != r1 || j != c1)) return;
	if(depth == m*n / 2 && (i != r2 || j != c2)) return;
	if(depth == 3 * m*n / 4 && (i != r3 || j != c3)) return;
	
	if(i == r1 && j == c1 && depth != m*n / 4) return;
	if(i == r2 && j == c2 && depth != m*n / 2) return;
	if(i == r3 && j == c3 && depth != 3 * m*n / 4) return;
	if(i == 0 && j == 1 && depth != m * n) return;
	
	if(depth == m * n) {
		if(i != 0 || j != 1) return;
		/*cout << "sol---------------------" << endl;
		FOR(x, 1, depth +1) {
			cout << id[x] <<","<<jd[x]<<endl;
		}
		moves[i][j] = '0';
		for(int x = m - 1; x >= 0; x--) {
			FOR(y, 0, n) {
				cout << moves[x][y];
			} cout << endl;
		} cout << endl;*/
		ways++;
		return;
	}
	
	memset(reachv,0,sizeof reachv);
	if(depth + reach(i,j) < m * n) return;
	//if(!reachv[0][1]) return;
	
	visited[i][j] = true;
	
	/*moves[i][j] = 'v',*/solve(i-1,j,depth+1);
	/*moves[i][j] = '<',*/solve(i,j-1,depth+1);
	/*moves[i][j] = '^',*/solve(i+1,j,depth+1);
	/*moves[i][j] = '>',*/solve(i,j+1,depth+1);
	
	//moves[i][j] = '%';
	visited[i][j] = false;
	
}

int main() {
	int c = 0;
	while(c++, cin >> m >> n && m && n) {
		cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3;
		memset(visited, 0, sizeof visited);
		memset(reachv, 0, sizeof reachv);
		ways = 0;
		
		cout << "Case " <<c << ": " << (solve(0,0,1), ways) << endl;
	}
}
