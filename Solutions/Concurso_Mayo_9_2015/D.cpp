/*
3 0
3 1
10 3
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

#define MOD 1000000007

int mod(int a, int b) {
	return ((a%b)+b)%b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {  
	int xx = y = 0;
	int yy = x = 1;
	while (b) {
		int q = a/b;
		int t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
	int x, y;
	int d = extended_euclid(a, n, x, y);
	if (d > 1) return -1;
	return mod(x,n);
}

int factA[2000010] = {0};
int fact(int n) {
	if (factA[n]) 
		return factA[n];
	else
		return factA[n] = n * fact(n-1) % MOD;
}

int invFactA[1000010] = {0};
int invFact(int n) {
	if (invFactA[n])
		return invFactA[n];
	else
		return invFactA[n] = mod_inverse(n, MOD) * invFact(n-1) % MOD;
}

int nCr(int n, int r) {
	int res = 1;
	res = (fact(n) * invFact(r))%MOD * invFact(n-r);
	return res%MOD;
}

mint main() {
	ios_base::sync_with_stdio(false);
	int n, k;
	factA[0] = invFactA[0] = 1;
	while (cin >> n >> k) {
		cout << nCr(n+k, k) << endl;
	}
}