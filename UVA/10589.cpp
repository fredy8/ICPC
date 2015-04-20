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

int main() {
	int n, a; 
	
	while(cin >> n >> a && n) {
		int m = 0;
		FOR(i, 0, n) {
			double x,y;
			cin >> x >> y;
			/*cout << x << "," << y << endl;
			cout << hypot(x,y) << endl;
			cout << hypot(a - x, a - y) << endl;
			cout << hypot(a - x,y) << endl;
			cout << hypot(x,a - y) << endl;*/
			
			if(hypot(x,y) <= a
				&& hypot(a - x, a - y) <= a
				&& hypot(a - x,y) <= a
				&& hypot(x,a - y) <= a) {
					//cout <<"vrai"<<endl;
					m++;
			}
			
		}
		
		cout << std::fixed << std::setprecision(5) <<
				(((double)m)*a*a/n) << endl;
	}
}
