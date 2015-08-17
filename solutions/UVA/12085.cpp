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


void prints(long long start, long long end) {
	if(start < 0) return;
	if(start == end) {
		cout << "0" << start << endl;
		return;
	}
	
	long long quot = 1, digs = 0;
					
	while(end / quot != start / quot) {
		quot *= 10;
		digs++;
	}
	
	cout << "0" << start << "-";
	
	cout << setfill('0') << setw(digs) << (end % quot) << endl;
}

int main() {
	int n, cs = 0;
	
	while(cin >> n, n) {
		cout << "Case " << ++cs << ":" << endl;
		long long prev = -100, start = -100;
		
		while(n--) {
			long long num; cin >> num;
			
			if(num != prev + 1) {
				prints(start, prev);
				start = num;
			}
			
			prev = num;
		}
		
		prints(start, prev);
		cout << endl;
	}
}
// a b a b a3
