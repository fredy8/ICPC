/*
6 4
3 1
2 1
1 2
1 3
3 3
0 0
4 3
3 4
1 1
1 1
5 6
10 5
7 8
4 9
3 7
5 9
7 2
10 3
0 10
3 2
6 3
7 9
0 0
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
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#define INF 1000000000
#define FOR(i, a, b) for(ll i=ll(a); i<ll(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

ll arr[200][2];
ll N;

ll memo[3][200][200];

ll solve(ll type, ll row, ll k) {
    if(!k)
        return 0;
    if(row == N)
        return INF;
    if(memo[type][row][k] != -1)
        return memo[type][row][k];

    if(type == 0) {
        return memo[type][row][k] = min(solve(1, row+1, k-1) + arr[row][0], min(solve(2, row+1, k-1) + arr[row][1], solve(0, row+1, k)));
    } else if(type == 1) {
        return memo[type][row][k] = min(solve(1, row+1, k-1)  + arr[row][0], solve(0, row+1, k));
    } else {
        return memo[type][row][k] = min(solve(2, row+1, k-1)  + arr[row][1], solve(0, row+1, k));
    }
}

int main() {
    ll k;
    while(cin >> N >> k && N) {
        ll sum = 0;

        FOR(i, 0, 3)
            FOR(j, 0, 200)
                FOR(k, 0, 200)
                    memo[i][j][k] = -1;

        FOR(i, 0, N) {
            cin >> arr[i][0] >> arr[i][1];
            sum += arr[i][0] + arr[i][1];
        }
        cout << sum-solve(0, 0, k) << endl;
    }
}