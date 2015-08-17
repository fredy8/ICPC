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

#define MAX 10010
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

vi sumList;
void buildSumList() {
    int last = 0;
    sumList.pb(0);
    for (int i = 0; i < primesList.size(); i++) {
        last += primesList[i];
        sumList.pb(last);
    }
}

bool isInSumList(int N) {
    return binary_search(sumList.begin(), sumList.end(), N);
}

int main()
{
    buildPrimesList();
    buildSumList();
    int n;
    while (cin >> n && n) {
        int t = 0, i = 0;
        while (primesList[i] <= n) {
            int sum = n + sumList[i];
            //cout << " " << i << " " << sum << endl;
            if (isInSumList(sum))
                 t++;
            i++;
        }
        cout << t << endl;
    }
}
