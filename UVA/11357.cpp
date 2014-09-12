
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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

#define EXPECT(expr) if(!(expr)) return -1;
#define MATCH(c) { assert(in.peek() == c); in.ignore();}


int main() {
	int n;
	
	cin >> n;
	
	bool has[27], hasneg[27];
	
	while(n--) {
		string s;
		cin >> s;
		stringstream in(s);
		
		
		bool sat = false;
		do {
			if(in.peek() == '|') MATCH('|');
			sat = true;
			MATCH('(');
			
			
			memset(has, 0, sizeof has);
			memset(hasneg, 0, sizeof hasneg);
			do {
				if(in.peek() == '&') MATCH('&');
				if(in.peek() == '~') {
					MATCH('~');
					int c = in.get();
					if(has[c - 'a']) {
						sat = false;
					}
					hasneg[c - 'a'] = true;
				} else {
					int c = in.get();
					if(hasneg[c - 'a']) {
						sat = false;
					}
					has[c - 'a'] = true;
				}
			} while(in.peek() == '&');
			MATCH(')');
			
		} while(!sat && in.peek() == '|');
			
		cout << (sat ? "YES" : "NO") << endl;
	}	
	
}
// a b a b a3
