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

int main()
{
    long long m;
    while (cin >> m && m) {
        long long n, s, x = 0, y = 0, d;
        n = ceil(sqrt(m));
        s = (n-1)*(n-1);
        d = m - s;
        if (d <= n) {
            x = n;
            y = d;
        } else {
            x = (n*n) - m + 1;
            y = n;
        }
        if (n%2 == 0)
            swap(x, y);
        cout << x << " " << y << endl;
    }
}
