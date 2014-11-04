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

vii split (string str, int &frst, int &sum)
{
    istringstream iss(str);
    vii v;
    ii n;
    int i = 0;
    iss >> frst;
    iss >> sum;
    sum = 0;
    while (iss >> n.first) {
        n.second = i++;
        sum += n.first;
        v.pb(n);
    }
    return v;
}

bool ord1(ii a, ii b) { return a.first > b.first; }
bool ord2(ii a, ii b) { return a.second < b.second; }

void getSolution (int n, int &best, int acum, int sum, int i, vii sp, vii curV, vii &rv)
{
    if (acum > n) return;
    if (acum + sum <= best) return;
    if (acum > best) {
        best = acum;
        rv = curV;
    }
    if (i >= sp.size()) return;
    getSolution(n, best, acum, sum-sp[i].first, i+1, sp, curV, rv);
    curV.pb(sp[i]);
    getSolution(n, best, acum+sp[i].first, sum-sp[i].first, i+1, sp, curV, rv);
}
int solve(int n, vii sp, int sum, vii &rv)
{
    int s = 0;
    vii curV;
    getSolution(n, s, 0, sum, 0, sp, curV, rv);
    return s;
}
int main()
{
    string str;
    while (getline(cin, str)) {
        int n, sum = 0;
        vii sp = split(str, n, sum), rv;
        sort(sp.begin(), sp.end(), ord1);
        int r = solve(n, sp, sum, rv);
        sort(rv.begin(), rv.end(), ord2);
        for (int i = 0; i < rv.size(); i++)
            cout << rv[i].first << " ";
        cout << "sum:" << r << endl;
    }
}
