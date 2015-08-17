
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
#include <unordered_set>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;


int main() {
	int n, m;
	
	while(cin >> n >> m, n || m) {
		unordered_set<int> jack;
		
		while(n--) {
			int x;
			cin >> x;
			jack.insert(x);
		}
		
		int total = 0;
		
		while(m--) {
			int x; cin >>x;
			if(jack.count(x)) total++;
		}
		
		cout << total << endl;
	}
	
	
}
// a b a b a3
