struct Vec {
    double x, y, z;
    Vec(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec() : x(0), y(0), z(0) {}
    Vec(double x, double y) : x(x), y(y), z(0) {}
    Vec(Point a, Point b) : x(b.x-a.x), y(b.y-a.y), z(b.z-a.z) {}
};

Vec toVec(Point a, Point b){
    return Vec(a, b); }

Vec scale(Vec v, double s) {
    return Vec(v.x*s, v.y*s, v.z*s); }

Point translate(Point p, Vec v) {
    return Point(p.x+v.x, p.y+v.y, p.z+v.z); }

double dot(Vec a, Vec b) {
    return (a.x*b.x + a.y*b.y + a.z*b.z); }

double norm_sq(Vec v) {
    return v.x*v.x + v.y*v.y + v.z*v.z; }

//angle in radians
Vec rotate(Vec v, double angle) {
    Matrix rotation(2, 2);
    rotation[0][0] = rotation[1][1] = cos(angle);
    rotation[1][0] = sin(angle);
    rotation[0][1] = -rotation[1][0];

    Matrix vec(2, 1);
    vec[0][0] = v.x, vec[0][1] = v.y;

    Matrix res = multiply(rotation, vec);
    Vec result(res[0][0], res[0][1]);
    return result;
}

double cross (Vec a, Vec b) { return a.x*b.y - a.y*b.x; }

// returns true if r is on the left side of line pq
bool ccw(Point p, Point q, Point r){
    return cross(toVec(p, q), toVec(p, r)) > 0; }

bool collinear(Point p, Point q, Point r) {
    return abs(cross(toVec(p, q), toVec(p, r))) < EPS; }

double angle(Point a, Point o, Point b) { // returns angle aob in rad
    Vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}
