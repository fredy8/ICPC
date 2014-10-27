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

void getDivisors(vii pf, int d, int index, vi &div)
{
	if (index == pf.size()) {
		div.pb(d);
		return;
	}
	for (int i = 0; i <= pf[index].second; i++) {
		getDivisors(pf, d, index+1, div);
		d *= pf[index].first;
	}
	return;
}

vi divisors(ll N) {
	vii pf = primeFactorization(N);
	vi div;
	getDivisors(pf, 1ll, 0, div);
	sort(div.begin(), div.end());
	return div;
}

bool isPrime(int n) {
	if(n < 2) return false;
	if(n == 2 || n == 3) return true;
	if(!(n&1 && n%3)) return false;
	long long sqrtN = sqrt(n)+1;
	for(long long i = 6LL; i <= sqrtN; i += 6)
		if(!(n%(i-1)) || !(n%(i+1))) return false;
	return true;
}
