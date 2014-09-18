

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


int main() {
	long long n;
	
	while(cin >> n, n) {
		long long a = 0, b = 0;
		
		int i = 0;
		
		while(n) {
			long long bit = (n & -n);
			if(i & 1)
				b |= bit;
			else
				a |= bit;
			
			n -= bit;
			i++;
		}
		
		cout << a << " " << b << endl;
	}
}
