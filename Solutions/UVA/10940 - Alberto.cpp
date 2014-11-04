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
    typedef vector<double> vd;
#endif

template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

int solve(int n)
{
    int d = n - pow(2, floor(log2(n)));
    if (d == 0) return n;
    return 2*d;
}

int main()
{
    int n;
    while (cin >> n && n) {
        cout << solve(n) << endl;
    }
}
