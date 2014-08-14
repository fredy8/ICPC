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
    using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
#endif

#define MAX 60010
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

bool isPrime(long long n) {
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(!(n&1 && n%3)) return false;
    long long sqrtN = sqrt(n)+1;
    for(long long i = 6LL; i <= sqrtN; i += 6)
        if(!(n%(i-1)) || !(n%(i+1))) return false;
    return true;
}

long long sumOfDivisors(int n) {
    vii pf = primeFactorization(n);
    long long r = 1;
    for (int i = 0; i < pf.size(); i++) {
        long long d;
        d = (pow(pf[i].first, pf[i].second + 1)-1)/(pf[i].first-1);
        r *= d;
    }
    return r-n;
}

int main()
{
    buildPrimesList();
    int n;
    cout << "PERFECTION OUTPUT" << endl;
    while (cin >> n && n) {
        int sod = sumOfDivisors(n);
        cout << setw(5) << n << "  ";
        if (sod > n)
            cout << "ABUNDANT" << endl;
        else if (sod < n)
            cout << "DEFICIENT" << endl;
        else
            cout << "PERFECT" << endl;
    }
    cout << "END OF OUTPUT" << endl;
}