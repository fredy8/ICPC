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

const double pi = acos(-1);

double ramanujan(ll n)
{
    return n*log(n) - n + (log(n) + log(1+4*n*(1+2*n)))/6 + log(pi)/2;
}
ll logncr (ll n, ll r)
{
    if (n == r || r == 0) return 1;
    return ceil((ramanujan(n) - ramanujan(n-r) - ramanujan(r))/log(10));
}
int main()
{
    ll n, r;
    while (cin >> n >> r)
        cout << logncr(n, r) << endl;
}
