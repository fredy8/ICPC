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

char table[6][6];

//char table[8][52][52];

#define m 4
#define n 4

int moov[8][2] = 
{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};


bool search(int i, int j, const string &word, int idx, ll used) {
	if(idx == word.size()) return true;
	if(table[i][j] != word[idx]
		|| used & (1LL << (i * 6 + j))) return false;
	
	FOR(d, 0, 8) {
		if(search(
			i+moov[d][0],
			j+moov[d][1], 
			word, 
			idx + 1,
			used | (1LL << (i * 6 + j))))
			return true;
	}
	
	return false;
}

int score(int s) {
	const int points[] = {0,0,0,1,1,2,3,5,11};
	return points[min(8, s)];
}

int main() {
	int t; cin >> t;
	
	FOR(game, 1, t+1) {
		//int m, n; cin >> m >> n;
		memset(table, 0, sizeof table);
		FOR(i, 1, 5) {
			cin >> (table[i] + 1);
		}
		
		/*FOR(i, 0, m+2) {
			FOR(j, 0, n+2) {
				cout << (table[i][j] ? table[i][j] : '-') << " ";
			} 
			cout << endl;
		}*/
		int sc = 0;
		int k; cin >> k;
		
		while(k--) {
			string word;
			cin >> word;
			
			
			FOR(i, 1, m+1)
				FOR(j, 1, n+1) {
					if(search(i, j, word, 0, 0)) {
						//cout << "found " << word << endl;
						sc += score(word.size());
						i = j = INF;
					}
				}
		}
		
		cout << "Score for Boggle game #" 
			<< game << ": " << sc << endl;
		
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
