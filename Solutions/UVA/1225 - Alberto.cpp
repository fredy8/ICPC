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

int memo[10001][10] = {{0}}, m = 0;

template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

void getDigits(int n) {
    if (m < n) {
        for (int i = m+1; i <= n; i++) {
            string num = toString<int>(i);
            for (int j = 0; j < num.length(); j++)
                memo[i][num[j] - '0']++;
            for (int j = 0; j < 10; j++)
                memo[i][j] += memo[i-1][j];
        }
        m = n;
    }
    for (int i = 0; i < 10; i++)
        cout << (i?" ":"") << memo[n][i];
    cout << endl;
}

int main()
{
    int casos;
    cin >> casos;
    while (casos--) {
        int n;
        cin >> n;
        getDigits(n);
    }
}