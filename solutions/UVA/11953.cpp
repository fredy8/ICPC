/*
2
4
x...
..x.
@.@.
....
2
..
x.
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
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int N;
string grid[100];

ii moves[] = {ii(1, 0), ii(0, 1), ii(-1, 0), ii(0, -1)};

bool FF(int r, int c, bool first) {

    if(grid[r][c] == 'x' || (grid[r][c] == '@' && !first)) {
        grid[r][c] = '.';

        FOR(i, 0, 4) {
            int nextR = r + moves[i].first;
            int nextC = c + moves[i].second;
            if(nextR >= 0 && nextR < N && nextC >= 0 && nextC < N) {
                FF(nextR, nextC, false);
            }
        }
        return true;
    }

    return false;
}

int main() {
    int TC;
    cin >> TC;
    FOR(tc, 1, TC+1) {
        cin >> N;
        FOR(i, 0, N) {
            cin >> grid[i];
        }

        int ans = 0;
        FOR(i, 0, N) 
            FOR(j, 0, N)
                ans += FF(i, j, true);

        printf("Case %d: %d\n", tc, ans);
    }
}