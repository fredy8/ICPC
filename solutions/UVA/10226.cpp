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
#include <unordered_map>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;



int main() {
	int n;
	cin >> n;
	
	while(n--) {
		while(isspace(cin.peek())) cin.ignore();
		
		map<string, int> trees;
		int total = 0;
		
		string s;
		while(getline(cin, s), s != "") {
			total++;
			trees[s]++;
		}
		
		FORC(trees, sp) {
			cout << sp->first << " " << fixed << setprecision(4) << (((double) 100 * sp->second) / total) << endl;
		}
		
		if(n > 0) cout << endl;
	}
}
// a b a b a3
