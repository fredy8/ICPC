#ifndef sh
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
    #define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
    #define pb push_back
    using namespace std; typedef pair<long long, long long> ii; typedef vector<long long> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
#endif

#define MAX 200000
bitset<MAX> sieve;
void buildSieve() {
    sieve.set();

    sieve[0] = sieve[1] = 0;
    int root = sqrt(MAX);
    FOR(i, 2, MAX)
        if (sieve[i] && i <= root)
            for(int j = i*i; j < MAX; j+=i)
                sieve[j] = 0;
}

vi primesList;
void buildPrimesList() {
    if(!sieve[2])
        buildSieve();
    primesList.reserve(MAX/log(MAX));
    FOR(i, 2, MAX+1)
        if(sieve[i])
            primesList.push_back(i);
}

vii primeFactorization(long long N) {
    vii factors;
    if (N == 1) return factors;
    long long idx = 0, pf = primesList[0];
    while(pf*pf <= N) {
        while(N%pf==0) {
            N /= pf;
            if(factors.size() && factors.back().first == pf)
                factors.back().second++;
            else
                factors.push_back(ii(pf, 1));
        }
        pf = primesList[++idx];
    }
    if(N!=1) factors.push_back(ii(N, 1));
    return factors;
}

bool dividesFact(long long d, long long n)
{
    if (d == 0) return false;
    vii pf = primeFactorization(d);
    for (int i = 0; i < pf.size(); i++) {
        long long p, k, t = 0;
        p = k = pf[i].first;
        while (k <= n) {
            t += n/k;
            k *= p;
        }
        if (t < pf[i].second) return false;
    }
    return true;
}
int main()
{
    buildPrimesList();
    long long d, n;
    while (cin >> n >> d) {
        if (dividesFact(d, n))
            cout << d << " divides " << n << "!" << endl;
        else
            cout << d << " does not divide " << n << "!" << endl;
    }
}
