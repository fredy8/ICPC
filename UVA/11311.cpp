
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
#include <cassert>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;


int main() {
	int n;
	
	cin >> n;
	
	while(n--) {
		int m, n, r, c;
		cin >> m >> n >> r >> c;
		
		if(r ^ c ^ (m - 1 - r) ^ (n - 1 - c))
			cout << "Gretel" << endl;
		else 
			cout << "Hansel" << endl;
		
	}	
	
}
// a b a b a3
