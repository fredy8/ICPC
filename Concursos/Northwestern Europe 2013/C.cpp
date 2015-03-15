/*
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

#define MAX 1100
double memo[MAX];

double prob(int i) {
    if (memo[i] >= 0) return memo[i];
    double s = 0;
    for (int j = 2; j <= 9; j++)
        s += prob(i+j);
    s += 4*prob(i+10);
    s += prob(i+11);
    return memo[i] = s/13;
}

int value(string c) {
    if (c == "J" || c == "Q" || c == "K" || c == "10") return 10;
    if (c == "A") return 11;
    return (c[0] - '0');
}

mint main()
{
    int n, m;
    cout << fixed << setprecision(10);
    while (cin >> n >> m) {
        for (int i = 0; i < MAX; i++)
            memo[i] = -1;
        memo[m] = 1;
        string c;
        for (int i = 0; i < n; i++) {
            cin >> c;
            m += value(c);
            memo[m] = 1;
        }
        m -= value(c);
        for (int i = m+1; i < MAX; i++)
            memo[i] = 0;
        double s = 0;
        for (int i = 1; i <= 10; i++)
            s += prob(i);
        cout << s/10 << endl;
    }
}
