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
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

typedef pair<ii, ii> segmento;

segmento makeSeg(ii p1, ii p2) {
    ll x = p2.first - p1.first;
    ll y = p1.second - p2.second;
    ll dist = x*x + y*y;
    ll gcd = __gcd(x, y);
    ll a = x/gcd;
    ll b = y/gcd;
    ll c = p1.first*b + p1.second*a;
    return mp(mp(a, b), mp(dist, c));
}

bool compara1(segmento a, segmento b) {
    return a.first == b.first && a.second.first == b.second.first;
}

bool compara2(segmento a, segmento b) {
    return a.second.second == b.second.second;
}

void displaySeg(segmento s) {
    cout << s.first.first << " " << s.first.second << " " << s.second.first << " " << s.second.second << endl;
}

int main()
{
    ll N, S = 0, x, y, total = 0;
    vii points;
    vector<segmento> segs;
    cin >> N;
    FOR(i, 0, N) {
        cin >> x >> y;
        points.pb(mp(x, y));
    }
    FOR(i, 0, N) {
        FOR(j, i+1, N) {
            segmento seg = makeSeg(points[i], points[j]);
            //cout << i << " " << j << " - ";
            //displaySeg(seg);
            S++;
            segs.pb(seg);
        }
    }
    //cout << "============" << endl;
    sort(segs.begin(), segs.end());
    //FOR(i, 0, S) {
    //    displaySeg(segs[i]);
    //}
    //cout << "============" << endl;
    for (int i = 0; i < S; i++) {
        int j = i+1;
        int t = 0;
        int cnt = 1;
        while (j < S && compara1(segs[i], segs[j])) {
            cnt++;
            j++;
        }
        if (cnt == 1) continue;
        //cout << i << " " << cnt << endl;
        for(; i < j; i++) {
            int cnt1 = 1;
            while (i+1 < j && compara2(segs[i], segs[i+1])) {
                i++;
                cnt1++;
            }
            //cout << " " << cnt1 << endl;
            t += cnt1*(cnt1-1)/2;
        }
        t = cnt*(cnt-1)/2 - t;
        total += t;
        i--;
    }
    cout << total/2 << endl;
}
