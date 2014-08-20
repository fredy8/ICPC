/*
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
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

ii moves[] = { ii(2, 1), ii(-2, 1), ii(2, -1), ii(-2, -1), 
               ii(1, 2), ii(1, -2), ii(-1, 2), ii(-1, -2) };

int solve(ii from, ii to) {
    
    if(from == to)
        return 0;

    bool visited[8][8];
    
    FOR(i, 0, 8)
        FOR(j, 0, 8)
            visited[i][j] = 0;

    queue<pair<ii, int> > q;
    q.push(make_pair(from, 0));
    visited[from.first][from.second] = 1;

    while(!q.empty()) {
        ii pos = q.front().first;
        int steps = q.front().second;
        q.pop();

        FOR(i, 0, 8) {
            ii next = ii(pos.first + moves[i].first, pos.second + moves[i].second);
            if(next.first >= 0 && next.first < 8 && next.second >= 0 && next.second < 8 && !visited[next.first][next.second]) {
                if(next == to) {
                    return steps + 1;
                }
                q.push(make_pair(next, steps+1));
                visited[next.first][next.second] = 1;
            }
        }
    }

    return -1;
}

int main() {
    string strfrom, strto;
    while(cin >> strfrom >> strto) {
        ii from = ii(strfrom[0] - 'a', strfrom[1] - '1');
        ii to = ii(strto[0] - 'a', strto[1] - '1');
        printf("To get from %s to %s takes %d knight moves.\n", strfrom.c_str(), strto.c_str(), solve(from, to));
    }
}