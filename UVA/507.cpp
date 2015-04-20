
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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;



int main() {
	int t; cin >> t;
	FOR(tc, 1, t+1) {
		int n;
		cin >> n;
		
		ii goodlen;
		int gli;
		goodlen.first = -1;
		
		int sum = 0, i = 0;
		
		FOR(j, 0, n-1) {
			int x; cin >> x;
			
			/*cout << "i " << i << " j " << j << " x " << x << endl;
			cout << "gli " << gli 
				<< " good " << goodlen.first 
				<< " len " << goodlen.second << endl;*/
			
			sum += x;
			if(sum < 0) {sum = 0; i = j + 1; continue;}
			ii ngl(sum, j - i);
			if(ngl > goodlen) {
				goodlen = ngl;
				gli = i;
			}
		}
		
		if(goodlen.first > 0) 
			cout << "The nicest part of route " << tc <<
				" is between stops " << (gli+1) << " and " 
				<< (gli+goodlen.second+2) << endl;
		else cout << "Route " << tc<< " has no nice parts" << endl;
	}
}
