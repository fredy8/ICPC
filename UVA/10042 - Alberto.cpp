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
    using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<char, char> cc;
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

int sumOfDigits(long long N) {
    int t = 0;
    while (N) {
        t += N%10;
        N /= 10;
    }
    return t;
}

bool isSmith(long long N) {
    vii pf = primeFactorization(N);
    if (pf.size() == 1 && pf[0].second == 1) return false;
    int sumN = 0, sumPF = 0;
    sumN = sumOfDigits(N);
    for (int i = 0; i < pf.size(); i++)
        sumPF += pf[i].second*sumOfDigits(pf[i].first);
    //cout << N << " " << sumN << " " << sumPF << endl;
    return (sumN == sumPF);
}

int main()
{
    buildPrimesList();
    int casos;
    cin >> casos;
    while (casos--) {
        long long n;
        cin >> n;
        do {
            n++;
        } while (!isSmith(n));
        cout << n << endl;
    }
}
