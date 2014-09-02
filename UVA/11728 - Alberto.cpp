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
    using namespace std; typedef long long ll; typedef pair<long long, long long> ii; typedef vector<long long> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
#endif

#define MAX 100
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
int sumOfDivisors(long long n)
{
    int t = 1;
    vii pf = primeFactorization(n);
    for (int i = 0; i < pf.size(); i++)
        t *= (pow(pf[i].first, pf[i].second + 1) - 1)/(pf[i].first-1);
    return t;
}
vi sums;
void fillSums()
{
    sums.assign(1001, -1);
    for (int i = 1; i < 1000; i++) {
        int s = sumOfDivisors(i);
        if (s <= 1000)
            sums[s] = i;
    }
}

int main()
{
    buildPrimesList();
    fillSums();
    int n, tc = 1;
    while (cin >> n && n) {
        cout << "Case " << tc << ": " << sums[n] << endl;
        tc++;
    }
}
