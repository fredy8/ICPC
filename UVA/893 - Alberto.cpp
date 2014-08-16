//624

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

long long toJulian(long long day, long long month, long long year) {
    return 1461 * (year + 4800 + (month - 14) / 12) / 4 +
        367 * (month - 2 - (month - 14) / 12 * 12) / 12 -
        3 * ((year + 4900 + (month - 14) / 12) / 100) / 4 +
        day - 32075;
}

void toGregorian(long long julian, long long &day, long long &month, long long &year) {
    long long x, n, i, j;
    x = julian + 68569;
    n = 4 * x / 146097;
    x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447;
    day = x - 2447 * j / 80;
    x = j / 11;
    month = j + 2 - 12 * x;
    year = 100 * (n - 49) + i + x;
}

int main()
{
    long long n, d, m, y;
    while (cin >> n >> d >> m >> y && d) {
        toGregorian(toJulian(d, m, y) + n, d, m, y);
        cout << d << " " << m << " " << y << endl;
    }
}
