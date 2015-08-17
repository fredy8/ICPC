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

map<pair<int, vi>, int> dp;
pair<int, vi> dpCheck;
int n, k, t, s, l[8] = {0};
vvi arr;

int fill(int);

int miniFill (int row, int col) {
    if (col > l[row]) return fill(row+1);
    int r = 0;
    for (int i = max(arr[row-1][col] + 1, arr[row][col-1]); i <= n; i++) {
        arr[row][col] = i;
        r += miniFill(row, col+1);
    }
    return r;
}

int fill(int row) {
    if (row > k) {t++; return 1;}
    dpCheck = mp(row, arr[row-1]);
    if (dp.find(dpCheck) != dp.end()) {
        s++;
        return dp[dpCheck];
    }
    return dp[dpCheck] = miniFill(row, 1);
}

mint main()
{
    while (cin >> k) {
        arr.clear();
        dp.clear();
        arr.assign(k+1, vi());
        for (int i = 1; i <= k; i++) {
            cin >> l[i];
            arr[i].assign(l[i] + 1, 0);
        }
        arr[0].assign(l[1]+1, 0);
        cin >> n;
        t = 0;
        s = 0;
        cout << fill(1) << endl;
        //cout << t << " " << s << endl;
        cout << dp.size() << endl;
    }
}
