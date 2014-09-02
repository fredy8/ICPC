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
template <typename T>
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }
template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

string reverse(string s)
{
    string r = "";
    for (int i = 0; i < s.length(); i++)
        r = s[i] + r;
    return r;
}
void solve(string n)
{
    string r = "", strA = "", strB = "", ceros = "";
    for (int i = 0; i < n.length(); i++) {
        //if (n[i] == '0') ceros += n[i];
        //else r += n[i];
        (n[i]=='0' ? ceros : r) += n[i];
    }
    sort(r.begin(), r.end());
    strA = reverse(r) + ceros;
    strB = r[0] + ceros + r.substr(1);
    ll a = toNum<ll>(strA), b = toNum<ll>(strB);
    cout << a << " - " << b << " = " << a-b << " = 9 * " << (a-b)/9 << endl;
}
int main()
{
    int n;
    while (cin >> n) {
        solve(toString<int>(n));
    }
}
