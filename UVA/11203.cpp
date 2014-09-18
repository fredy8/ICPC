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
	int n; cin >> n;
	
	while(n--) {
		string t; cin >> t;
		
		int i = 0, j, a = 0, b = 0, c = 0;
		
		while(i < t.size() && t[i] == '?') i++, a++;
		
		if(i == t.size() || t[i] != 'M') {
			cout << "no-theorem" << endl;
			continue;
		}
		
		i++;
		while(i < t.size() && t[i] == '?') i++, b++;
		if(i == t.size() || t[i] != 'E') {
			cout << "no-theorem" << endl;
			continue;
		}
		
		i++;
		while(i < t.size() && t[i] == '?') i++, c++;
		
		if(i !=t.size()) {
			cout << "no-theorem" << endl;
			continue;
		}
		
		if(!a || !b || !c || c != a + b) {
			cout << "no-theorem" << endl;
		} else cout << "theorem" << endl;
	}
}
