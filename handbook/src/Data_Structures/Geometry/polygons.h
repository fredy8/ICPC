/* Polygons
*/
typedef vector<Point> Polygon;

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

// works for convex and concave
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
bool isSimple(const Polygon &p) {
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
		if (left1 > -EPS) P.pb(Q[i]);
		if (left1 * left2 < -EPS)
			P.pb(lineIntersectSeg(Q[i], Q[i+1], a, b));
	}
	if (!P.empty() && !(P.back() == P.front()))
		P.pb(P.front());
	return P;
}

// only works for convex
bool pointInPolygon(Polygon &p1, Point p) {
  FOR(i, 0, p1.size() - 1)
    if (cross(p1[i], p1[i+1], p) >= 0)
      return false;
  return true;
}

// polygons must be convex
// returns polygon with size < 3 if there is no intersection
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
  return convexHull(p);
}
