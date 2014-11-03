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

char table[103][103];

//char table[8][52][52];

int moov[8][2] = 
{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

int main() {
	
		int m, n; cin >> m;
		n = m;
		memset(table[0], 0, n + 2);
		memset(table[m + 1], 0, n + 2);
		FOR(i, 1, m + 1) {
			table[i][0] = 0;
			cin >> (table[i] + 1);
		}
		
		/*FOR(i, 0, m+2) {
			FOR(j, 0, n+2) {
				cout << (table[i][j] ? table[i][j] : '-') << " ";
			} 
			cout << endl;
		}*/
		
		//int k; cin >> k;
		
			string word;
			
		while(cin >> word, word != "0") {
			
			int ipos, jpos, dpos;
			
			FOR(i, 1, m+1)
				FOR(j, 1, n+1) {
					FOR(d, 0, 8) {
						int idx = 0;
						
						int li, lj;
						li = i+(word.size()-1)*moov[d][0];
						lj = j+(word.size()-1)*moov[d][1];
						
						if(li < 1 || li > m || lj < 1 || lj > n)
							continue;
						
						while(
							toupper(table
								[i+idx*moov[d][0]][j+idx*moov[d][1]])
							== toupper(word[idx]) 
							&& idx < word.size()) idx++;
						
						if(idx == word.size()) {
							ipos = i; jpos = j; dpos = d;
							goto found;
						}
							
					}
				}
			cout << "Not found" << endl;
			continue;
			
			found:
			cout << ipos << "," << jpos << " "
			<< (ipos+(word.size()-1)*moov[dpos][0]) 
			<< "," << (jpos+(word.size()-1)*moov[dpos][1]) << endl;	
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
