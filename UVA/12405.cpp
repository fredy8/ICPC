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
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int mark[104];

#define CHAR(i) s[(i) - 1]

int main() {
	int c = 1, T;
	string s;
	cin >> T;
	for(;c <= T; c++) {
		int n; cin >> n;
		cin >> s;
		memset(mark, 0, sizeof mark);
		
		int use = 0;
		
		FOR(i, 0, n) {
			if(s[i] == '.') {
				mark[i]++;
				mark[i+1]++;
				mark[i+2]++;
				use++;
			}
		}
		
		int scare = 0;
		
		for(int k = 3; k > 0; k--) {
			FOR(i, 1, n + 1) {
				if(mark[i] == k && use) {
					scare++;
					if(i > 1 && CHAR(i - 1) == '.') {
						mark[i - 2]--;
						mark[i - 1]--;
						mark[i]--;
						
						CHAR(i - 1) = '#';
						use--;
					}
					if(CHAR(i) == '.') {
						mark[i - 1]--;
						mark[i]--;
						mark[i + 1]--;
						
						CHAR(i) = '#';
						use--;
					}
					if(i < 100 && CHAR(i + 1) == '.') {
						mark[i]--;
						mark[i + 1]--;
						mark[i + 2]--;
						
						CHAR(i + 1) = '#';
						use--;
					}
				}
			}
		}
		
		cout << "Case " << c << ": " << scare << endl;
		
		
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
