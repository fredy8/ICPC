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
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int main()
{
    int N, p, s, r;
    vi players, dif, acum;
    cin >> N;
    FOR(i, 0, N) {
        cin >> p;
        players.pb(p);
    }
    sort(players.begin(), players.end());
    FOR(i, 0, N/2) {
        dif.pb(players[2*i+1] - players[2*i]);
    }
    sort(dif.begin(), dif.end());
    acum.pb(0);
    FOR(i, 0, N/2) {
        acum.pb(acum[i] + dif[i]);
    }
    s = acum[N/2];
    r = lower_bound(acum.begin(), acum.end(), (s+1)/2) - acum.begin() - 1;
    cout << r << endl;
}
