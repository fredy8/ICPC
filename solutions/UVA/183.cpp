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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

char mapa[201][201];

void fill(char x, int i, int j, int h, int w) {
	FOR(ix,i,i+h)
		FOR(jx,j,j+w)
			mapa[ix][jx] = x;
}

int dtob(string &s, int pos, int i, int j, int h, int w) {
	if(!w || !h) return pos;
	if(isdigit(s[pos])) {
		fill(s[pos++], i, j, h, w);
	} else { // D
		pos++;
		pos = dtob(s, pos, i, 		j,			h - h/2, 	w - w/2);
		pos = dtob(s, pos, i, 		j+w-w/2,	h - h/2, 	w/2);
		
		pos = dtob(s, pos, i+h-h/2, j, 			h/2, 		w - w/2);
		pos = dtob(s, pos, i+h-h/2, j+w-w/2, 	h/2, 		w/2);
	}
	return pos;
}

bool allis(char x, int i, int j, int h, int w) {
	FOR(ix,i,i+h)
		FOR(jx,j,j+w)
			if(mapa[ix][jx] != x) return false;
	return true;
}

string btod(int i, int j, int h, int w) {
	if(!w || !h) return "";
	if(allis('1',i,j,h,w)) return "1";
	if(allis('0',i,j,h,w)) return "0";
	return "D" 
		+ btod(i, 		j,			h - h/2, 	w - w/2)
		+ btod(i, 		j+w-w/2,	h - h/2, 	w/2)
		
		+ btod(i+h-h/2, 	j, 			h/2, 		w - w/2)
		+ btod(i+h-h/2, 	j+w-w/2, 	h/2, 		w/2);
}

int main() {
	char c;
	
	/*FOR(t, 0, 100) {
		cout << "B " << 100 << " " << 100 << endl;
		
		FOR(i, 0, 100) {
			FOR(j, 0, 100) {
				cout << (rand() % 2) ;
			} cout << endl;
		};
		
	} cout << "#" << endl;
	
	return 0;/**/
	
	while(cin >> c,c!='#') {
		int h,w; cin >> h >> w;
		string s,x; //cin >> s;
		s.reserve(h*w);
		
		for(; s.size() < h * w; cin >> x, s += x);
		
		if(c == 'B') {
			FOR(i, 0, h)
				FOR(j, 0, w)
					mapa[i][j] = s[i * w + j];
			printf("D%4d%4d\n", h, w);
			
			string m = btod(0, 0, h, w);
			
			FOR(c, 0, m.size()) {
				cout << m[c];
				if((c + 1) % 50 == 0 || c == m.size()-1) cout << endl;
			}
			
			
		} else {
			int pos = dtob(s, 0, 0, 0, h, w);
			assert(pos == s.size());
			
			printf("B%4d%4d\n", h, w);
			
			FOR(i, 0, h)
				FOR(j, 0, w) {
					cout << mapa[i][j];
				}
			cout << endl;
		}
		
		
	}
}
