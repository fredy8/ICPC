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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

// http://www.win.tue.nl/~sthite/mincircle/mincircle.java

struct point {
	double x, y;
	point(double x_, double y_) : x(x_), y(y_) {}
	point(const point&a) : x(a.x), y(a.y) {}
	point(){}
}
;
struct circle {
	double r; point c;
	circle(point c_, double r_) : c(c_), r(r_) {}
};

double dist(const point&a, const point &b) {
	return hypot(a.x - b.x, a.y - b.y);
}

circle circ(point p1, point p2, point p3 ) {
	double x = (p3.x*p3.x * (p1.y - p2.y) 
		+ (p1.x*p1.x + (p1.y - p2.y)*(p1.y - p3.y)) 
		* (p2.y - p3.y) + p2.x*p2.x * (-p1.y + p3.y)) 
		/ (2 * (p3.x * (p1.y - p2.y) + p1.x * (p2.y - p3.y) + p2.x 
		* (-p1.y + p3.y)));

	double y = (p2.y + p3.y)/2 - (p3.x - p2.x)/(p3.y - p2.y) 
		* (x - (p2.x + p3.x)/2);

	point c(x, y);
	double r = dist(c, p1);

	return circle(c, r);
}

circle mincirc(int n, point *p, int m, point *b){
	point c(-1,-1);
	double r = 0;

	if(m == 1) {
		c = point(b[0]);
		r = 0;
	} else if(m == 2) {
		c = point((b[0].x+b[1].x)/2, (b[0].y+b[1].y)/2);
		r = dist(b[0], c);
	} else if(m == 3)
		return circ(b[0], b[1], b[2]);


	circle minC(c, r);

	for(int i = 0;  i < n;  i++ )
		if(dist(p[i], minC.c) > minC.r) {
			b[m] = point(p[i]);

			minC = mincirc(i, p, m+1, b);
		}

	return minC;
}



int main() {
	int n; 
	
	point p[101], b[10];
	
	while(cin >> n, n) {
		FOR(i, 0, n) cin >> p[i].x >> p[i].y;
		
		double rr; cin >> rr;
		
		if(mincirc(n, p, 0, b).r<=rr + 1e-9)
			cout << "The polygon can be packed in the circle." << endl;
		else
			cout <<"There is no way of packing that polygon." << endl;
	}
}
