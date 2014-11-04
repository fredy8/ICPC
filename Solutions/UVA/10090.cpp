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

void extendedEuclidean (ll a, ll b, ll &x, ll &y, ll &r) {
    ll r0 = a, r1 = b, s0 = 1, t0 = 0, s1 = 0, t1 = 1;
    while(r1) {
        ll aux, q;
        aux = r1;
        q = r0 / r1;
        r1 = r0 % r1;
        r0 = aux;
        aux = s1;
        s1 = s0 - q * s1;
        s0 = aux;
        aux = t1;
        t1 = t0 - q * t1;
        t0 = aux;
    }
    if(r0 < 0) r0 = -r0, s0 = -s0, t0 = -t0;
    r = r0, x = s0, y = t0;    
}



int main() {
	ll n;
	
		ll c1, n1, c2, n2,m, m2;
	while(cin >> n, n) {
		
		cin >> c1 >> n1 >> c2 >> n2;
		//cout << "n1 "<< n1  << "n2 "<< n2 << endl;
		
		ll x,y,r;
		
		extendedEuclidean(n1, n2, x, y, r);
		//cout << x << "," << y << endl;
		//cout << x * (n / r) << " " 
		//	<< y * (n / r) << endl; 
			
		ll cx = x * (n / r), cy = y * (n / r);
		// xv = cx + n2*v >= 0
		ll av = -cx / n2;
		// yv = cy - n1*v >= 0
		ll bv = cy / n1;
		
		
		ll lv = min(av, bv), hv = max(av, bv);
		
		
		//cout << lv << " - " << hv << endl;
		
		ll bestx, besty, bestsum = INF;
		
		for(ll v = lv - 1; v <= lv + 3;v++) {
			ll rx = cx + n2 * v, ry = cy - n1 * v, sum = rx * c1 + ry * c2;
			
			//cout << "rx " << rx << " ry " << ry << " sum " << (rx + ry) << " cost " << endl;
			
			if(rx >= 0 && ry >= 0 &&sum < bestsum) {
				bestsum = sum;
				bestx = rx; besty = ry;
			}
		}
		
		for(ll v = hv + 1; v >= hv - 3;v--) {
			ll rx = cx + n2 * v, ry = cy - n1 * v, sum = rx * c1 + ry * c2;
			
			//cout << "rx " << rx << " ry " << ry << " sum " << (rx + ry) << " cost " << endl;
			
			if(rx >= 0 && ry >= 0 &&sum < bestsum) {
				bestsum = sum;
				bestx = rx; besty = ry;
			}
		}
		
		if(bestsum < INF)
			cout << bestx << " " << besty << endl;
		else cout << "failed" << endl;
		
		// minimizar c1*xv + c2*yv
	}
}
