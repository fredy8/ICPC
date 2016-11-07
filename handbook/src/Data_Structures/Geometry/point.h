/* Point
*/
const double PI = 2*asin(1);

bool eq(double a, double b) { return fabs(a-b) < EPS; }
bool les(double a, double b) { return !eq(a, b) && a < b; }
struct Point {
	double x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(double x, double y) : x(x), y(y), z(0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	bool operator <(const Point &p) const {
        return les(x, p.x) || (eq(x, p.x) && les(y, p.y)) || (eq(x, p.x) && eq(y, p.y) && les(z, p.z));
	}
    bool operator==(const Point &p) {
        return eq(x, p.x) && eq(y, p.y) && eq(z, p.z);
    }
};

double DEG_to_RAD(double deg) {
    return deg/180*2*asin(1);
}

double dist(Point p1, Point p2) {
	return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2) + pow(p1.z-p2.z, 2)); }
	
Point rotate(Point p, double theta) {
	double rad = DEG_to_RAD(theta);
	return Point(p.x*cos(rad) - p.y*sin(rad),
				 p.x*sin(rad) + p.y*cos(rad));
}

double ANG(double rad) { return rad*180/PI; }
double angulo(Point p) {
	double d = atan(double(p.y)/p.x);
	if(p.x < 0)
		d += PI;
	else if(p.y < 0)
		d += 2*PI;
	return ANG(d);
}