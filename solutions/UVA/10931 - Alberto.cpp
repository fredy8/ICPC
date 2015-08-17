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

string toBinary(int n, int &cnt)
{
    string r = "";
    while (n) {
        if (n%2) {
            cnt++;
            r = '1'+r;
        } else {
            r = '0'+r;
        }
        n /= 2;
    }
    return r;
}

int main()
{
    int n;
    while (cin >> n && n) {
        int cnt = 0;
        string bin = toBinary(n, cnt);
        cout << "The parity of " << bin << " is " << cnt << " (mod 2)." << endl;
    }
}
