
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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int finished[10001];

int main() {
	int m, n;
	
	while(cin >> m >> n) {
		map<ii, int> b;
		FOR(i, 1, m + 1) {
			while(isspace(cin.peek())) cin.ignore();
			string s1;
			getline(cin, s1);
			if(s1 == "0") {
				continue;
			}
			string s2;
			getline(cin, s2);
			
			stringstream ss1(s1), ss2(s2);
			int x;
			ss1 >> x;
			//cout << "rlen " << x << endl;
			
			while(x--) {
				int j;
				ss1 >> j;
				int val;
				ss2 >> val;
				
				b[ii(j, i)] = val;
				//cout << "b("<<i<<","<<j<<") = "<< val<< endl;
			}
			
			
		}
		
		//cout << " ENDR " << endl;
		
		cout << n << " " << m << endl;
		
		stringstream ss1(""), ss2("");
		
		int i = 0, rc = 0;
		FORC(b, it) {
			/*cout << "proc " 
				<< it->first.first << "," << it->first.second
				<< " = " << it->second << " rc " << rc << " i " << i << endl;*/
			if(it->first.first > i) {
				if(rc) {
					cout << rc << " " << ss1.str() << endl
						<< ss2.str() << endl;
				}
				
				FOR(r, i + rc + 1, it->first.first) {
					cout << 0 << endl << endl;
				}
				
				rc = 0;
				i = it->first.first;
				
				ss1.str(string());
				ss1.clear();
				ss2.str(string());
				ss2.clear();
			}
			
			rc++;
			ss1 << (ss1.str().empty() ? "" : " ") << it->first.second;
			ss2 << (ss2.str().empty() ? "" : " ") << it->second;
			
			//cout << "1end \"" << ss1.str() << "\"" << endl;
			//cout << "2end \"" << ss2.str() << "\"" << endl;
		}
		
				if(rc) {
					cout << rc << " " << ss1.str() << endl
						<< ss2.str() << endl;
				}
				
				FOR(r, i + rc + 1, m + 1) {
					cout << 0 << endl << endl;
				}
		
	}
}
// a b a b a3
