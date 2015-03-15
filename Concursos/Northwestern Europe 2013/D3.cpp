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
#include <fstream>
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
int n, k, t, l[8] = {0}, cnt;
vvi arr;
ofstream arc;

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
    if (row > k) {return 1;}
    dpCheck = mp(row, arr[row-1]);
    if (dp.find(dpCheck) != dp.end()) {
        return dp[dpCheck];
    }
    return dp[dpCheck] = miniFill(row, 1);
}

void display() {
    int d = 0;
    for (int i = 1; i <= k; i++) {
        d *= 8;
        d += l[i];
    }
    arc << "arr[" << k << "][" << n << "][" << d << "] = " << t << ";" << endl;
}

void solve() {
    arr.clear();
    dp.clear();
    arr.assign(k+1, vi());
    for (int i = 1; i <= k; i++) {
        arr[i].assign(l[i] + 1, 0);
    }
    arr[0].assign(l[1]+1, 0);
    t = fill(1);
    display();
}

void fillLengths(int ind, int prev) {
    if (ind > k) {
        cnt++;
        if (cnt%20 == 0) cout << ".";
        for (n = k; n <= 7; n++)
            solve();
    } else {
        for (int i = prev; i >= 1; i--) {
            l[ind] = i;
            fillLengths(ind+1, i);
        }
    }
}

mint main()
{
    arc.open("outputD.txt");
    for (k = 1; k <= 7; k++) {
        cnt = 0;
        cout << k;
        fillLengths(1, 7);
        cout << endl;
    }
    arc.close();
}
