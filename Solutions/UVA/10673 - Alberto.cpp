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

//d = ax + by
void extendedEuclid(int a, int b, int &x, int &y, int &d) {
    if(!b) { x = 1; y = 0; d = a; return; }
    extendedEuclid(b, a%b, x, y, d);
    int x1 = y;
    int y1 = x - (a/b)*y;
    x = x1, y = y1;
}

int main()
{
    int casos;
    cin >> casos;
    while (casos--) {
        int m, k, a, b, x, y, d;
        cin >> m >> k;
        a = ceil((double)m/k);
        b = floor((double)m/k);
        extendedEuclid(a, b, x, y, d);
        cout << x*m/d << " " << y*m/d << endl;
    }
}
