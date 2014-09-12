
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
		int n, t, m;
		
		cin >> n >> t >> m;
		
		//priority_queue<ii, less<ii> > left;
		//priority_queue<ii, less<ii> > right;
		queue<ii> banks[2]; //left, right;
		
		
		FOR(i, 0, m) {
			int arr;
			string s;
			
			cin >> arr >> s;
			
			if(s == "left") {
				banks[0].push(ii(arr, i));
			} else {
				banks[1].push(ii(arr, i));
			}
		}
		
		banks[0].push(ii(INF, -1));
		banks[1].push(ii(INF, -1));
		
		int it = 0;
		int curr = 0;
		
		while(banks[0].front().first < INF || banks[1].front().first < INF) {
			//cout << "c"<<curr << endl;
			if(banks[it].front().first > curr) {
				int mi = 
					min(banks[0].front().first, banks[1].front().first);
				//cout << "miis" << mi << endl;
				if(mi != banks[it].front().first) {
					curr = max(curr, mi) + t; // go to the other side
					it ^= 1;
					continue;
				} else curr = mi;
			}
			
			//cout << "xc"<<curr << endl;
			
			int picked = 0;
			
			while(banks[it].front().first <= curr
				&& picked < n) {
				
				finished[banks[it].front().second]  = curr + t;
				banks[it].pop();
				picked++;
			}
			curr += t;
			
			//cout << "xc"<<curr << endl;
			
			it ^= 1; // heh
		}
		
		FOR(i, 0, m) {
			cout << finished[i] << endl;
		}
		if(c > 0) cout << endl;
	}
}
// a b a b a3
