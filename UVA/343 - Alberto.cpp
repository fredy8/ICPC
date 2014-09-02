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

string toBaseN(long long num, int N) {
    string converted;
    for(long long div=num; div; div /= N) {
        int value = div % N;
        char c = value > 9 ? value + 'A' - 10 : value + '0';
        converted = c + converted;
    }
    return converted;
}

long long toBase10(string num, int b) {
    long long res = 0, k = 1;
    for(int i=num.length()-1; i>=0; i--) {
        char c = toupper(num[i]);
        int value = c > '9' ? c - 'A' + 10 : c - '0';
        res += (value)*k;
        k*=b;
    }
    return res;
}

int minBase (string X)
{
    char m;
    for (int i = 0; i < X.length(); i++)
        m = max(m, X[i]);
    if (m <= '9') return m-'0'+1;
    return m-'A'+11;
}

void solve (string X, string Y)
{
    vi x, y;
    int mx = minBase(X), my = minBase(Y);
    for (int i = 0; i <= 36; i++) {
        x.pb(mx <= i ? toBase10(X, i) : -1);
        y.pb(my <= i ? toBase10(Y, i) : -1ll);
    }
    int A = -1, B = -1;
    for (int i = 1; i <= 36; i++) {
        if (x[i] == -1) continue;
        for (int j = 1; j <= 36; j++) {
            if (x[i] == y[j]) {
                A = i;
                B = j;
                break;
            }
        }
        if (A != -1) break;
    }
    if (A == -1) {
        cout << X << " is not equal to " << Y << " in any base 2..36" << endl;
    } else {
        cout << X << " (base " << A << ") = " << Y << " (base " << B << ")" << endl;
    }
}

int main()
{
    string X, Y;
    while (cin >> X >> Y) {
        solve(X, Y);
    }
}
