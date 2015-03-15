
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


int main() {
	int n;
	while(cin >> n) {
		
		
		stack<int> s;
		queue<int> q;
		priority_queue<int> p;
		
		int pos = 7;
		
		while(n--) {
			int c, v;
			
			cin >> c >> v;
			
			if(c == 1) {
				s.push(v);
				q.push(v);
				p.push(v);
			} else {
				assert(c == 2);
				if(s.empty() || s.top() != v) {
					pos &= ~1;
				}
				if(q.empty() || q.front() != v) {
					pos &= ~2;
				}
				if(p.empty() || p.top() != v) {
					pos &= ~4;
				}
				
				
				if(!s.empty()) s.pop();
				if(!q.empty()) q.pop();
				if(!p.empty()) p.pop();
			}
		}
		
		if(pos == 1) {
			cout << "stack"<< endl;
		} else
		
		if(pos == 2) {
			cout << "queue"<< endl;
		} else
		
		if(pos == 4) {
			cout << "priority queue"<< endl;
		} else
		
		if(pos == 0) {
			cout << "impossible"<< endl;
		} else
		
		{
			cout << "not sure"<< endl;
		}
	}
	
	
}
// a b a b a3
