typedef vector<Point> Polygon;
typedef long long ll;

ll cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
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

// return area when Points are in cw or ccw, p[0]  = p[n-1]
double area(const Polygon &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].x; x2 = P[i+1].x; 
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1*y2-x2*y1);
    }
    return abs(result) / 2.0;
}

bool isConvex(const Polygon &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;
    bool isLeft = ccw(P[0], P[1], P[2]);
    for (int i = 1; i < sz-1; i++)
        if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
            return false;
    return true;
}

bool inPolygon (Point pt, const Polygon &P) {
    if((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);
        else sum -= angle(P[i], pt, P[i+1]); }
    return abs(abs(sum) - 2*PI) < EPS;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const Polygon &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (lineSegIntersect(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}

Point lineIntersectSeg(Point p, Point q, Point A, Point B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x*A.y - A.x*B.y;
    double u = abs(a*p.x + b*p.y + c);
    double v = abs(a*q.x + b*q.y + c);
    return Point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

// cuts polygon Q along line AB
Polygon cutPolygon(Point a, Point b, const Polygon &Q) {
    Polygon P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i+1])), left2 = 0;
        if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
        if (left1 > -EPS) P.push_back(Q[i]);
        if (left * left2 < -EPS)
            P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());
    return P;
}
