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



int main() {
	string s;
	
	while(getline(cin, s), s != "Game Over") { // ug
		int score = 0;
		int mul[30];
		FOR(i, 0, 25) mul[i] = 1;
		int roll = 0;
		int f = 0;
		int prev = 0;
		
		for(int i = 0; i < s.size(); i += 2) {
			if(s[i] == 'X') {
				if(f < 9) {
					mul[roll + 1]++;
					mul[roll + 2]++;
				}
				prev = 10;
				score += mul[roll++] * 10;
				f++;
			} else { // digit
				int frame = (s[i] != '/') ? s[i] - '0' : 10 - prev;
				prev = frame;
				score += mul[roll++] * frame;
				
				if(f < 10) {
					i += 2;
					if(s[i] == '/') {
						if(f < 9) mul[roll + 1]++;
						score += mul[roll++] * (10 - frame);
					} else {
						score += mul[roll++] * (s[i] - '0');
					}
				} else {
					
				}
				f++;
			}
		}
		
		cout << score << endl;
	}
}
// a b a b a3
