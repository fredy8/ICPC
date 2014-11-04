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

int n, k, t, l[8] = {0}, arr[8][8] = {{0}};

void fill(int row, int col) {
    if (row > k) {t++; return;}
    if (col > l[row]) {return fill(row+1, 1);}
    for (int i = max(arr[row-1][col] + 1, arr[row][col-1]); i <= n; i++) {
        arr[row][col] = i;
        fill(row, col+1);
    }
    return;
}

mint main()
{
    while (cin >> k) {
        for (int i = 1; i <= k; i++) cin >> l[i];
        cin >> n;
        t = 0;
        fill(1, 1);
        cout << t << endl;
    }
}
