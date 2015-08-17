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

// diag = n*(n-3)/2;

long long diagInv(long long n)
{
    long long sq = sqrt(2*n);
    for (long long i = sq+3;; i--) {
        if (i*(i-3)/2 < n) return i+1;
    }
    return -1;
}

int main()
{
    for (int tc = 1;; tc++) {
        long long n;
        cin >> n;
        if (!n) break;
        cout << "Case " << tc << ": " << diagInv(n) << endl;
    }
}
