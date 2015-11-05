/*
6 3 2 2 4 3 6 6 6 7 4 6 2 2 2
4 18 5 22 9 26 5 22 1 -2 1
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
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define RFORC(cont, it) for(decltype((cont).rbegin()) it=(cont).rbegin(); it!=(cont).rend(); it++)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

const double EPS = 1e-7;

struct Point {
  double x, y;
  Point() : x(0), y(0) {}
  Point(int x, int y): x(x), y(y) {}
  bool operator < (Point other) const {
    if (fabs(x - other.x) > EPS) return x < other.x;
    return y < other.y;
  }
  bool operator == (Point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }

  bool operator >= (Point other) const {
    return !(*this < other);
  }
};

typedef vector<Point> Polygon;


double cross(const Point &O, const Point &A, const Point &B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

struct Line {
  double a, b, c;
  Line() : a(0), b(0), c(0) {}
  Line(Point p1, Point p2) {
    if(abs(p1.x-p2.x) < EPS) {
      a = 1.0; b = 0.0; c = -p1.x;
    } else {
      a = -(double)(p1.y-p2.y)/(p1.x-p2.x);
      b = 1.0;
      c = -(double)(a*p1.x)-p1.y;
    }
  }
};

bool areParallel(Line l1, Line l2) {
  return (abs(l1.a-l2.a) < EPS) && (abs(l1.b-l2.b) < EPS); }

bool areSame(Line l1, Line l2) {
  return areParallel(l1, l2) && (abs(l1.c-l2.c) < EPS); }

bool areIntersect(Line l1, Line l2, Point &p) {
  if (areParallel(l1, l2)) return false;
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  if (abs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
  else                 p.y = -(l2.a * p.x + l2.c);
  return true;
}

double getIntTime(Point p0, Point pf, double vx, double vy) {
  if (fabs(vx) > EPS)
    return (pf.x - p0.x)/vx;
  return (pf.y - p0.y)/vy;
}

bool checkPointInSegm(Point p, Point sp1, Point sp2) {
  if (fabs(sp1.x - sp2.x) > EPS) {
    double pleft = sp1.x, pright = sp2.x;
    if (pleft > pright) swap(pleft, pright);
    return p.x >= pleft && p.x <= pright;
  }

  double pdown = sp1.y, pup = sp2.y;
  if (pdown > pup) swap(pdown, pup);
  return p.y >= pdown && p.y <= pup;
}

double minIntTime(Polygon &p1, Polygon &p2, double vx, double vy) {
  double minIntTime = INF;
  int N = p1.size(), M = p2.size();
  FOR(i, 0, N) {
    Point l1p1(p1[i].x, p1[i].y);
    Point l1p2(p1[i].x + vx, p1[i].y + vy);
    Line l1(l1p1, l1p2);
    FOR(j, 0, M) {
      Point l2p1(p2[j].x, p2[j].y);
      Point l2p2(p2[(j+1)%M].x, p2[(j+1)%M].y);
      Line l2(l2p1, l2p2);
      if (areSame(l1, l2)) {
        minIntTime = min(minIntTime, min(getIntTime(p1[i], p2[j], vx, vy), getIntTime(p1[i], p2[(j+1)%M], vx, vy)));
      } else if (!areParallel(l1, l2)) {
        Point intersect;
        bool b = areIntersect(l1, l2, intersect);
        if (b && checkPointInSegm(intersect, p2[j], p2[(j+1)%M])) {
          double intTime = getIntTime(p1[i], intersect, vx, vy);
          minIntTime = min(minIntTime, intTime);
        }
      }
    }
  }
  return minIntTime;
}

void printPoly(Polygon intL) {
  FOR(i, 0, intL.size()) cout << intL[i].x << " " << intL[i].y << endl;
    cout << endl;
}

int N, M;
Polygon p1, p2;
double vx, vy;

void translate(Polygon &p, double t, Polygon &ret) {
  ret.assign(p.begin(), p.end());
  FOR(i, 0, p.size()) {
    ret[i].x += t*vx;
    ret[i].y += t*vy;
  }
}

double area(const Polygon &P) {
  if (P.size() <= 2) return 0;
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size()-1; i++) {
    x1 = P[i].x; x2 = P[i+1].x;
    y1 = P[i].y; y2 = P[i+1].y;
    result += (x1*y2-x2*y1);
  }
  return abs(result) / 2.0;
}

bool pointInPolygon(Polygon &p1, Point p) {
  FOR(i, 0, p1.size() - 1)
    if (cross(p1[i], p1[i+1], p) >= 0)
      return false;
  return true;
}

Polygon convexHull(Polygon &P) {
  int n = P.size(), k = 0;
  Polygon H(2*n);
  sort(P.begin(), P.end());
  FOR(i, 0, n) {
    while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
    H[k++] = P[i];
  }
  for (int i = n-2, t = k+1; i >= 0; i--) {
    while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
    H[k++] = P[i];
  }
  H.resize(k);
  return H;
}

Polygon intersection(Polygon &p1, Polygon &p2) {
  set<Point> result;
  FOR(i, 0, p1.size() - 1) {
    if (pointInPolygon(p2, p1[i]))
      result.insert(p1[i]);
    FOR(j, 0, p2.size() - 1) {
      Line l1 = Line(p1[i], p1[i+1]);
      Line l2 = Line(p2[j], p2[j+1]);
      vector<Point> ps1, ps2;
      ps1.pb(p1[i]); ps1.pb(p1[i+1]);
      ps2.pb(p2[j]); ps2.pb(p2[j+1]);
      sort(ps1.begin(), ps1.end());
      sort(ps2.begin(), ps2.end());
      if (!areParallel(l1, l2)) {
        Point intersect;
        bool b = areIntersect(l1, l2, intersect);
        if (b && checkPointInSegm(intersect, ps1[0], ps1[1]) && checkPointInSegm(intersect, ps2[0], ps2[1]))
          result.insert(intersect);          
      } else if (areSame(l1, l2)) {
        if (ps1[1] >= ps2[0] && ps2[1] >= ps1[0]) {
          vector<Point> ps3;
          ps3.pb(ps1[0]); ps3.pb(ps1[1]); ps3.pb(ps2[0]); ps3.pb(ps2[1]);
          sort(all(ps3));
          result.insert(ps3[1]);
          result.insert(ps3[2]);
        }
      }
    }
  }

  FOR(i, 0, p2.size() - 1) {
    if (pointInPolygon(p1, p2[i]))
      result.insert(p2[i]);
  }

  if (result.size() <= 2) {
    return Polygon(result.begin(), result.end());
  }

  Polygon p(result.begin(), result.end());
  // printPoly(p);
  return convexHull(p);
}

int main() { _
  while(cin >> N) {
    p1.assign(N, Point());
    FOR(i, 0, N)
      cin >> p1[i].x >> p1[i].y;
    cin >> vx >> vy;

    cin >> M;
    p2.assign(M, Point());
    FOR(i, 0, M)
      cin >> p2[i].x >> p2[i].y;

    int a, b;
    cin >> a >> b;
    vx -= a, vy -= b;

    double lo = min(minIntTime(p1, p2, vx, vy), minIntTime(p2, p1, -vx, -vy));
    if (lo <= 0 || lo >= INF) {
      cout << "never" << endl;
      return 0;
    }

    Polygon p3;
    translate(p1, 100000, p3);

    p1.pb(p1[0]);
    p2.pb(p2[0]);

    double hi = 100000 - min(minIntTime(p3, p2, -vx, -vy), minIntTime(p2, p3, vx, vy));
    while(fabs(lo - hi) > 1E-11) {
      double mid = (lo + hi)/2;
      Polygon left, right;
      translate(p1, mid - 1E-6, left);
      translate(p1, mid + 1E-6, right);
      Polygon intL = intersection(left, p2), intR = intersection(right, p2);
      // printPoly(intL);
      double aleft = area(intL);
      double aright = area(intR);
      // cout << aleft << " " << aright << endl;
      if (aleft < aright) lo = mid;
      else hi = mid;
    }

    cout << (lo + hi)/2 << endl;
  }
}
