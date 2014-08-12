struct Triangle {
    Point A, B, C;
    Triangle() : A(Point()), B(Point()), C(Point()) {}
    Triangle(Point A, Point B, Point C) : A(A), B(B), C(C) {}
};

double perimeter(double a, double b, double c) { return a+b+c; }

// Heron's formula
double area(double a, double b, double c){
    double s = perimeter(a, b, c)*0.5;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double rInCircle(double ab, double bc, double ca){
    return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

double rInCircle(Point a, Point b, Point c) {
    return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

bool inCircle(Point p1, Point p2, Point p3, Point &ctr, double &r) {
    r = rInCircle(p1, p2, p3);
    if(abs(r) < EPS) return false;
    Line l1, l2;
    double ratio = dist(p1, p2) / dist(p1, p3);
    Point p = translate(p2, scale(toVec(p2, p3), ratio/(1+ratio)));
    l1 = Line(p1, p);
    ratio = dist(p2, p1) / dist(p2, p3);
    l2 = Line(p2, p);
    areIntersect(l1, l2, ctr);
    return true;
}

Point circumcenter(Point A, Point B, Point C) {
    double D = 2*(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
    double AA = A.x*A.x + A.y*A.y, BB = B.x*B.x + B.y*B.y, CC = C.x*C.x + C.y*C.y;
    return Point((AA*(B.y - C.y) + BB*(C.y - A.y) + CC*(A.y - B.y)) / D, (AA*(C.x - B.x) + BB*(A.x - C.x) + CC*(B.x - A.x)) / D);
}