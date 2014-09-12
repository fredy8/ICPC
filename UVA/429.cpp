
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
#include <unordered_map>
#include <unordered_set>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;


int main() {
	int n;
	
	cin >> n;
	
	while(n--) {
		unordered_map<string, vector<char> > words;
		
		while(isspace(cin.peek())) cin.ignore();
		
		string s;
		while(cin >> s, s != "*") {
			FOR(i, 0, s.size()) {
				char z = s[i];
				s[i] = '*';
				words[s].push_back(z);
				s[i] = z;
			}
		}
		
		while(isspace(cin.peek())) cin.ignore();
		
		while(getline(cin, s), s != "") {
			stringstream ss(s);
			string a, b;
			ss >> a >> b;
			
			queue<pair<string, int> > q;
			unordered_set<string> visited;
			
			q.push(pair<string, int>(a, 0));
			
			while(!q.empty()) {
				string s = q.front().first;
				int steps = q.front().second;
				q.pop();
				
				visited.insert(s);
				assert(visited.count(s));
				
				if(s == b) {
					cout << a << " " << b << " " << steps << endl;
					break;
				}
				
				FOR(i, 0, s.size()) {
					char z = s[i];
					s[i] = '*';
					
					vector<char>& vc = words[s];
					
					FORC(vc, it) {
						s[i] = *it;
						
						if(!visited.count(s)) {
							q.push(pair<string, int>(s, steps + 1));
						}
					}
					
					
					
					s[i] = z;
				}
				
			}
		}
	}	
	
}
// a b a b a3
