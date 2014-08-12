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

// Interseccion de AB con CD
// * WARNING: Does not work for collinear line segments!
bool lineSegIntersect(Point a, Point b, Point c, Point d) {
    double ucrossv1 = cross(toVec(a, b), toVec(a, c));
    double ucrossv2 = cross(toVec(a, b), toVec(a, d));
    if (ucrossv1 * ucrossv2 > 0) return false;
    double vcrossu1 = cross(toVec(c, d), toVec(c, a));
    double vcrossu2 = cross(toVec(c, d), toVec(c, b));
    return (vcrossu1 * vcrossu2 <= 0);
}

// Calcula la distancia de un punto P a una recta AB, y guarda en C la inters
double distToLine(Point p, Point a, Point b, Point &c) {
    Vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

// Distancia a de P a segmento AB
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { c = a; return dist(p, a); }
    if (u > 1.0) { c = b; return dist(p, b); }
    return distToLine(p, a, b, c);
}

