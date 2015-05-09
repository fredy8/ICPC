/*
1
3
9
10
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

#define SIZE 1000000
bitset<SIZE> sieve;
void buildSieve() {
	sieve.set();
	sieve[0] = sieve[1] = 0;
	int root = sqrt(SIZE);
	FOR(i, 2, root+1)
		if (sieve[i])
			for(int j = i*i; j < SIZE; j+=i)
				sieve[j] = 0;
}

vi primesList;
void buildPrimesList() {
	if(!sieve[2])
		buildSieve();
	primesList.reserve(SIZE/log(SIZE));
	FOR(i, 2, SIZE+1)
		if(sieve[i])
			primesList.pb(i);
}

vii primeFactorization(int N) {
	vii factors;
	int idx = 0, pf = primesList[0];
	while(pf*pf <= N) {
		while(N%pf==0) {
			N /= pf;
			if(factors.size() && factors.back().first == pf)
				factors.back().second++;
			else
				factors.pb(ii(pf, 1));
		}
		pf = primesList[++idx];
	}
	if(N!=1) factors.pb(ii(N, 1));
	return factors;
}

int numOfDivisors(int n) {
	vii pf = primeFactorization(n);
	int t = 1;
	FOR(i, 0, pf.size()) {
		t *= pf[i].second + 1;
	}
	return t;
}

mint main() {
	ios_base::sync_with_stdio(false);
	buildPrimesList();
	int n;
	while (cin >> n) {
		int m = n;
		while (m%2==0) m/=2;
		int d = numOfDivisors(m);
		int r = (d/2)*2 + (d%2) - 1;
		cout << r << endl;
	}
}