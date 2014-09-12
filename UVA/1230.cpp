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

ll power(ll x, ll n, ll m) {
	ll res = 1;
	x %= m;
	
	while(n > 0) {
		if(n & 1) {
			res = (res * x) % m;
		}
		n >>= 1;
		x = (x * x) % m;
	}
	
	return res;
}

int main() {
	int c; cin >> c;
	
	while(c--) {
		ll x, y,z;
		cin >> x >> y >> z;
		
		cout << power(x, y, z) << endl;
	}
}

/*
 * 
3755PR/1E/9V6
5377BR/12/9WU
5707BA/12/9V6
5327BA/1E/9V6
7337BA/1E/9V6
7137BA/11/9V6

*/
