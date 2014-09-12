
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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;



int main() {
	int cs; cin >> cs;
	
	FOR(cs, 1, cs + 1) {
		int b; cin >> b;
		
		vi h(b), w(b), im(b, -1), iw(b,0), dm(b, INF), dw(b,0);
		;
		
		FOR(i, 0, b) cin >> h[i];
		FOR(i, 0, b) cin >> w[i];
		
		FOR(i, 0, b) {
			im[i] = h[i], iw[i] = w[i];
			
			FOR(j, 0, i) {
				if(h[i] > im[j]) {
					if(iw[j] + w[i] > iw[i]) {
						
					}
				}
			}
		}
	}
}
