
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
	int n;
	
	while(cin >> n, n) {
		int sum = 0, maxi = 0;
		while(n--) {
			int x;
			cin >> x;
			sum += x;
			
			maxi = max(sum, maxi);
			if(sum < 0) sum = 0;
		}
		
		if(maxi > 0)
			cout << "The maximum winning streak is " << maxi << "." << endl;
		else
			cout << "Losing streak." << endl;
	}
}
