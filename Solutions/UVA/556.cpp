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
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

const int mv[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};


int main() {
	int b, w;
	
	while(cin >> b >> w, b || w) {
		vector<string> map;
		map.reserve(b + 2);
		map.push_back(string(w + 2, '1'));
		
		for(int i = 1; i <= b; i++) {
			map.push_back(string());
			map[i].reserve(w + 2);
			cin >> map[i];
			map[i].insert(0, 1, '1');
			map[i].push_back('1');
			//map[i] = "1" + map[i] + "1"; // expensive
		}
		
		map.push_back(string(w + 2, '1'));
		
		FOR(i, 0, map.size()) {
			cout << map[i] << endl;
		}
		cout << endl;
		
		bool moved = false;
		
		vvi visited(b + 2, vi(w + 2, 0));
		
		int i = b, j = 1, o = 0;
		
		while(!moved || !(i == b && j == 1)) {
			cout << "at " << i <<"," << j << endl;
			cout << "nx " << (i+ mv[o][0]) <<"," << (j + mv[o][1]) << endl;
			while(map[i + mv[o][0]][j + mv[o][1]] != '0' 
				|| map[i + mv[(o + 3) % 4][0]][j + mv[(o + 3) % 4][1]] != '1' ) {
					
				cout << "cy " << i <<"," << j 
					<< " ris " << (i + mv[(o + 3) % 4][0]) 
					<<"," << (j + mv[(o + 3) % 4][1]) << ":" << 
					map[i + mv[(o + 3) % 4][0]][j + mv[(o + 3) % 4][1]]<< endl;
				o = (o + 1) % 4;
			}
			if(moved)visited[i][j]++;
			moved = true;
			i += mv[o][0];
			j += mv[o][1];
		}
		
		int c[5] = {0};
		
		for(int i = 1; i <= b; i++) {
			for(int j = 1; j <= w; j++) {
				if(visited[i][j] < 5) {
					c[visited[i][j]]++;
				}
			}
		}
		
		cout << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << " " << c[4] << endl;
	}
	
	
}
