
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
	int c;
	cin >> c;
	
	while(c--) {
		int l, m;
		
		cin >> l >> m;
		l *= 100;
		
		//priority_queue<ii, less<ii> > left;
		//priority_queue<ii, less<ii> > right;
		queue<int> banks[2]; //left, right;
		
		
		FOR(i, 0, m) {
			int len;
			string s;
			
			cin >> len >> s;
			
			if(s == "left") {
				banks[0].push(len);
			} else {
				banks[1].push(len);
			}
		}
		
		int it = 0;
		
		while(!banks[0].empty() || !banks[1].empty()) {
			//cout << "c"<<curr << endl;
			int curr = 0;
			
			while(!banks[it % 2].empty()
				&& curr + banks[it % 2].front() <= l)
				
				curr += banks[it % 2].front(),
				banks[it % 2].pop();
			
			it++;
		}
		
		cout << it << endl;
	}
}
// a b a b a3
