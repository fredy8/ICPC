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

#define MAX 100000
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

bool isPrime(long long p) {
    if (p < MAX) return binary_search(primesList.begin(), primesList.end(), p);
    for (int i = 0; primesList[i]*primesList[i] <= p; i++)
        if (p%primesList[i] == 0) return false;
    return true;
}

long long fastPow(long long a, long long n, long long mod) {
    if(n == 0) return 1;
    if(n == 1) return a;
    long long t = fastPow(a, n>>1, mod);
    return t*t%mod*fastPow(a, n&1, mod)%mod;
}

int main()
{
    buildPrimesList();
    long long a, p;
    while (cin >> p >> a && p && a) {
        if (!isPrime(p) && (fastPow(a, p, p)-a)%p == 0)
            cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
