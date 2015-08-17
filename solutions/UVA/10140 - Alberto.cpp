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

#define MAX 1000000
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

int binarySearch (int i) // indice del primer primo mayor o igual a i
{
    int lo = 0, hi = primesList.size()-1;
    while (true) {
        //cout << lo << " " << hi << endl;
        int mid = (lo+hi)/2;
        if (lo == mid) return lo;
        if (primesList[mid] == i) {
            return mid;
        } else if (primesList[mid] < i) {    // p[m-1] < i <= p[m] return m
            if (primesList[mid+1] >= i) return mid+1;
            lo = mid;
        } else {                             // p[m] < i <= p[m+1] return m+1
            if (primesList[mid-1] < i) return mid;
            hi = mid;
        }
    }
}

void solve(int l, int u)
{
    int a = binarySearch(l);
    int b = binarySearch(u+1)-1;
    int mn = INF, mx = 0, mni = -1, mxi = -1;
    for (int i = a; i < b; i++) {
        if (primesList[i+1] - primesList[i] < mn) {
            mn = primesList[i+1] - primesList[i];
            mni = i;
        }
        if (primesList[i+1] - primesList[i] > mx) {
            mx = primesList[i+1] - primesList[i];
            mxi = i;
        }
    }
    if (mni == -1) {
        cout << "There are no adjacent primes." << endl;
    } else {
        cout << primesList[mni] << "," << primesList[mni+1];
        cout << " are closest, ";
        cout << primesList[mxi] << "," << primesList[mxi+1];
        cout << " are most distant." << endl;
    }
}

int main()
{
    int l, u;
    buildPrimesList();
    while (cin >> l >> u) {
        solve(l, u);
    }
}
