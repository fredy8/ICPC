/*
4
1 2 3 4
10
2 1 4 5 3 7 8 9 10 6
10
1 2 3 4 5 6 7 8 9 10
14
2 3 4 5 6 7 8 9 1 11 10 13 14 12
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

#define SIZE 100000
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

#define MOD 1000000007

int mod(int a, int b) {
	return ((a%b)+b)%b;
}

int modpow(int base, int exp, int modulus) {
	base = mod(base, modulus);
	int result = 1;
	while (exp) {
		if (exp & 1) result = mod(result * base, modulus);
		base = mod(base * base, modulus);
		exp >>= 1;
	}
	return result;
}

mint main() {
	buildPrimesList();
	int N;
	while (scanf("%lld", &N) != EOF) {
		vi sizes, visited(N, 0), arr(N, 0);
		
		FOR(i, 0, N)
			scanf("%lld", &arr[i]), arr[i]--;

		FOR(i, 0, N) if (!visited[i]) {
			int current = i, size = 0;
			while(!visited[current]) {
				visited[current] = 1;
				size++;
				current = arr[current];
			}
			sizes.pb(size);
		}

		int ans[1000001] = {0};
		FOR(i, 0, sizes.size()) {
			vii pf = primeFactorization(sizes[i]);
			FORC(pf, it)
				ans[it->first] = max(ans[it->first], it->second);
		}

		int total = 1;
		FOR(i, 0, 1000001) if (ans[i])
			total = (total * (int)pow(i, ans[i])) % MOD;

		printf("%lld\n", total);
	}
}