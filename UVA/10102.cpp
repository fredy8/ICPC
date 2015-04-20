/*
4
1223
2123
2213
3212
2
12
33
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
string arr[1000];
int dist[1000][1000];

ii moves[] = {ii(1, 0), ii(0, 1), ii(-1, 0), ii(0, -1)};

void solve(vii &initials) {
    queue<pair<int, ii> > q;
    memset(dist, 0, sizeof dist);

    FORC(initials, it) {
        dist[it->first][it->second] = 1;
        q.push(make_pair(1, *it));
    }

    while(!q.empty()) {
        int d = q.front().first;
        ii pos = q.front().second;
        q.pop();
        FOR(i, 0, 4) {
            ii next(pos.first + moves[i].first, pos.second + moves[i].second);
            if(next.first >= 0 && next.second < N && next.first < N && next.second >=0 && !dist[next.first][next.second]) {
                q.push(make_pair(d+1, next));

                dist[next.first][next.second] = d+1;
            }
        }
    }
}

int main() {
    while(cin >> N) {
        vii initials;
        FOR(i, 0, N) {
            cin >> arr[i];
            FOR(j, 0, N)
                if(arr[i][j] == '3')
                    initials.pb(ii(i, j));
        }

        solve(initials);


        int MAX = 0;
        FOR(i, 0, N)
            FOR(j, 0, N)
                if(arr[i][j] == '1')
                    MAX = max(MAX, dist[i][j]-1);
        cout << MAX << endl;
    }
}