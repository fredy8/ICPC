/*
3
1 1
5 6
6 5
4
1 1
1 100000000
100000000 1
100000000 100000000
4
1 1
3 5
5 3
5 5
5
50000000 1
50000000 99999999
1 50000000
99999999 50000000
50000001 50000001

*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std;
typedef long long ll; typedef pair<int, int> ii;
typedef vector<int> vi; typedef vector<ii> vii;
typedef vector<vi> vvi;

struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
};

bool comparaTL(Point a, Point b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y > b.y;
}

bool comparaTR(Point a, Point b) {
	if (a.x != b.x) return a.x > b.x;
	return a.y > b.y;
}

bool comparaBL(Point a, Point b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool comparaBR(Point a, Point b) {
	if (a.x != b.x) return a.x > b.x;
	return a.y < b.y;
}

mint main() {
	vector<Point> pointsTL;
	vector<Point> pointsTR;
	vector<Point> pointsBL;
	vector<Point> pointsBR;
	int V, A, P, x, y; 
	int minX = INF, maxX = 0, minY = INF, maxY = 0;
	cin >> V;
	FOR(i, 0, V) {
		Point p;
		cin >> p.x >> p.y;
		maxX = max(maxX, p.x);
		minX = min(minX, p.x);
		maxY = max(maxY, p.y);
		minY = min(minY, p.y);
		pointsTL.pb(p);
		pointsTR.pb(p);
		pointsBL.pb(p);
		pointsBR.pb(p);
	}
	maxX++; maxY++; minX--; minY--;
	A = (maxX - minX)*(maxY - minY);
	P = 2*((maxX - minX)+(maxY - minY));
	sort(pointsTL.begin(), pointsTL.end(), comparaTL);
	x = minX;
	y = pointsTL[0].y;
	FOR(i, 1, pointsTL.size()) {
		Point p = pointsTL[i];
		if (p.y <= y) continue;
		int w = p.x - x - 1;
		int h = maxY - y - 1;
		x = p.x - 1;
		Point q(x, y + 1);
		y = p.y;
		pointsBR.pb(q);
		//cout << 1 << " " << h*w << endl;
		A -= h*w;
	}
	sort(pointsTR.begin(), pointsTR.end(), comparaTR);
	x = maxX;
	y = pointsTR[0].y;
	FOR(i, 1, pointsTR.size()) {
		Point p = pointsTR[i];
		if (p.y <= y) continue;
		int w = x - p.x - 1;
		int h = maxY - y - 1;
		x = p.x + 1;
		Point q(x, y + 1);
		y = p.y;
		pointsBL.pb(q);
		//cout << 2 << " " << h*w << endl;
		A -= h*w;
	}
	sort(pointsBL.begin(), pointsBL.end(), comparaBL);
	x = minX;
	y = pointsBL[0].y;
	FOR(i, 1, pointsBL.size()) {
		Point p = pointsBL[i];
		if (p.y >= y) continue;
		int w = p.x - x - 1;
		int h = y - minY - 1;
		x = p.x - 1;
		y = p.y;
		//cout << 3 << " " << h*w << endl;
		A -= h*w;
	}
	sort(pointsBR.begin(), pointsBR.end(), comparaBR);
	x = maxX;
	y = pointsBR[0].y;
	FOR(i, 1, pointsBR.size()) {
		Point p = pointsBR[i];
		if (p.y >= y) continue;
		int w = x - p.x - 1;
		int h = y - minY - 1;
		x = p.x + 1;
		y = p.y;
		A -= h*w;
		//cout << 4 << " " << h*w << endl;
	}
	cout << P << " " << A << endl;
}
