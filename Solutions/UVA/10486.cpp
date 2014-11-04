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
#include <unordered_map>

#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;


int nxt[1000001][60];

int main() {
	string s;
	
	cin >> s;
	int t; cin >> t;
	
	FOR(i, 0, 60) nxt[s.size()-1][i] = -1;
	
	for(int i = s.size() - 2; i >= 0; i--) {
		FOR(j, 0, 60) {
			if(s[i] == 'A' + j)
				nxt[i][j] = i;
			else nxt[i][j] = i < s.size() - 1 ? nxt[i+1][j] : -1;	
		}
		
	}
	
	while(t--) {
		string sub;
		cin >> sub;
		unordered_map<ll, ii> memo;
		
		int ms = -1, me = -1, j = 0;
		
		/*FOR(i, 0, s.size()) {
			if(s[i] == sub[j]) {
				if(j == 0) ms = i;
				if(j == sub.size() - 1) {
					me = i;
					break;
				}
				
				j++;
			}
		}*/
		
		int i = 0;
		while(j < sub.size() && i < s.size()) {
			i = nxt[i][sub[j] - 'A'];
			if(i != -1) {
				//cout << "m " << j << "-"<< sub[j] << endl;
				if(j == 0) ms = i;
				if(j == sub.size() - 1) {
					me = i;
					break;
				}
				i++;
				j++;
			}
		}
		
		if(me == -1) cout << "Not matched" << endl;
		else cout << "Matched " << ms << " " << me << endl;
		continue;
		
		
	}
}
// a b a b a3
