#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;

int visited[501][501][4];
int conf[501][501];
int x[256];

int nwsetoi(char *nwse) {
	int res = 0;
	
	res |= x[nwse[0]];
	if(nwse[1]) {
		res |= x[nwse[1]];
		if(nwse[2]) {
			res |= x[nwse[2]];
			if(nwse[3]) {
				res |= x[nwse[3]];
			}
		}
	}
	
	
	return res;
}

int rota(int otn, int r) {
	return (otn >> r | otn << (4 - r)) & 0xf;
}

int main() {
	x['N'] = 0x1;
	x['W'] = 0x2;
	x['S'] = 0x4;
	x['E'] = 0x8;
	
	int r, c;
	char nwse[5];
	
	while(cin >> r >> c) {
		memset(visited, 0, sizeof visited);
		
		//for(int i = 0; i < r; i++) {
		//	for(int j = 0; i + j < r + c - 2; j++) {
		for(int z = 0; z < r * c - 1; z++) {
			int i = z / c, j = z % c;
			cin >> nwse;
				
			conf[i][j] = nwsetoi(nwse);
		}
		//	}
		//	cout << endl;
		//}
		
		bool found = false;
		queue<pair<ii, int> > q;
		
		q.push(pair<ii, int>(ii(0, 0), 0));
		
		while(!q.empty()) {
			int i = q.front().first.first,
				j = q.front().first.second;
			int step = q.front().second;
			q.pop();
			
			
			if(i >= 0 && i < r
				&& j >= 0 && j < c
				&& !visited[i][j][step % 4]) {
			
				if(i == r - 1 && j == c - 1) {
					cout << step << endl;
					found = true;
					break;
				}	
					
				visited[i][j][step % 4] = true;
				
				int otn = conf[i][j];
				otn =  rota(otn, step % 4);
					
				if(otn & 0x1)
					q.push(pair<ii, int>(ii(i - 1, j), step + 1));
				if(otn & 0x2)
					q.push(pair<ii, int>(ii(i, j - 1), step + 1));
				if(otn & 0x4)
					q.push(pair<ii, int>(ii(i + 1, j), step + 1));
				if(otn & 0x8)
					q.push(pair<ii, int>(ii(i, j + 1), step + 1));
			}
		}
		
		
		
		if(!found) cout << "no path to exit"<< endl;
	}
}
