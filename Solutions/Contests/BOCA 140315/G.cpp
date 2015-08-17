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
#define INF 1000000000000000
#define EPS 10e-8
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef pair<double, double> dd;

double dist(dd p1, dd p2) {
    double x = p1.first - p2.first;
    double y = p1.second - p2.second;
    return sqrt(x*x + y*y);
}

dd diff(const dd p1, const dd p2) {
    return mp(p2.first - p1.first, p2.second - p1.second);
}

dd sum(const dd p1, const dd p2) {
    return mp(p2.first + p1.first, p2.second + p1.second);
}

pair<dd, dd> getCenters(dd p1, dd p2, const double r, bool &p) {
    dd midPoint = mp((p1.first + p2.first)/2, (p1.second + p2.second)/2);
    double l = dist(midPoint, p1);
    if (l > r) {
        p = false;
        return mp(p1, p2);
    }
    double d = sqrt(r*r - l*l);
    dd vecToPoints = diff(midPoint, p1);
    dd vecToCenters = mp(vecToPoints.second/l*d, -vecToPoints.first/l*d);
    dd center1 = diff(vecToCenters, midPoint);
    dd center2 = sum(vecToCenters, midPoint);
    return mp(center1, center2);
}

mint main() {

    int n;
    cin >> n;
    while (n--) {
        int m, most = 1;
        double r;
        vector<dd> mosquitos;
        cin >> m >> r;
        r /= 2;
        FOR(i, 0, m) {
            double x, y;
            cin >> x >> y;
            mosquitos.pb(mp(x, y));
        }
        FOR(i, 0, m) {
            FOR(j, 0, i) {
                bool p = true;
                pair<dd, dd> centers = getCenters(mosquitos[i], mosquitos[j], r, p);
                if (!p) continue;
                int count1 = 0, count2 = 0;
                FOR(k, 0, m) {
                    if (dist(mosquitos[k], centers.first) <= r + EPS)
                        count1++;
                    if (dist(mosquitos[k], centers.second) <= r + EPS)
                        count2++;
                }
                most = max(most, max(count1, count2));
            }
        }
        cout << most << endl;
    }
}
