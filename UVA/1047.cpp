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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int only[21], bitm[11], inter[11];

int bc = 0, bbit;

int n, k;
int m;
void find(int depth, int idx, int bit, int total) {
	if(depth == k) {
		FOR(i, 0, m) {
			if(bit & bitm[i]) total += inter[i];
		}
		
		if(total > bc) {
			bc = total;
			bbit = bit;
		}
	} else {
		FOR(i, idx, n - (k - depth) + 1) {
			find(depth+1, i + 1, bit | (1 << i), total + only[i]);
		}
	}
}

int main() {
	int cas = 0;
	while(cin >> n >> k, (n || k)) {
		//if(cas) cout << endl;
		cas++;
		FOR(i,0,n) cin >> only[i];
		
		cin >> m;
		FOR(i,0,m) {
			int x; cin >> x;
			
			int bitmsk= 0;
			
			FOR(j, 0, x) {
				int y; cin >> y;
				bitmsk |= 1 << (y-1);
			}
			
			int tot; cin >> tot;
			
			bitm[i] = bitmsk;
			inter[i] = tot;
			
			FOR(j, 0, n) {
				if(bitmsk & (1 << j)) only[j] -= tot;
			}
		}
		
		bc = 0;
		
		find(0, 0, 0, 0);
		
		cout << "Case Number  " << cas <<endl;
		cout << "Number of Customers: " << bc <<endl;
		cout << "Locations recommended:";
		
		FOR(j, 0, n) {
			if(bbit & (1 << j)) cout << " " << (j+1) ;
		}
		cout << endl << endl;
	}
	
	
}
