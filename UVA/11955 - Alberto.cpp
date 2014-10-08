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
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }
template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

#define MAXN 51
long long pascal[MAXN][MAXN];
void buildPascal() {
	FOR(n, 0, MAXN)
		FOR(r, 0, n+1)
			pascal[n][r] = (r == 0 || r == n) ? 1 : pascal[n-1][r-1] + pascal[n-1][r];
}

int main()
{
    buildPascal();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string eq, a, b;
        cin >> eq;
        int pos1 = eq.find('+'), pos2 = eq.find(')'), n;
        a = eq.substr(1, pos1-1);
        b = eq.substr(pos1+1, pos2-pos1-1);
        n = toNum<int>(eq.substr(pos2+2));
        cout << "Case " << tc << ": ";
        for (int i = 0; i <= n; i++) {
            cout << (i?"+":"") << (pascal[n][i]==1?"":toString<ll>(pascal[n][i])+"*");
            cout << (n-i?a:"") << (n-i>1?"^"+toString<int>(n-i):"");
            cout << (n-i&&i?"*":"") << (i?b:"") << (i>1?"^"+toString<int>(i):"");
        }
        cout << endl;
    }
}
