/*
130a303
*/
// Locos
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

int count(string &s, int from, int to) {
	if(to < from) return 0;
	if(to == from) return !isdigit(s[from]) ? 0 : (s[from] -'0') % 3 == 0;
	
	int mid = (from + to) / 2;

	int total = count(s, from, mid);
	total += count(s, mid+1, to);

	int cuenta[3] = {0};
	int suma = 0;
	
	for(int i = mid; i >= from && isdigit(s[i]); i--) {
		suma += s[i] - '0';
		suma %= 3;

		cuenta[suma]++;

	}
	
	suma = 0;

	for(int i = mid + 1; i <= to && isdigit(s[i]); i++) {
		suma += s[i] - '0';
		suma %= 3;

		total += cuenta[(3 - suma) % 3];
	}
	
	return total;
}


mint main() {
	string s;
	cin >> s;
	cout << count(s, 0, s.size()-1) << endl;
}
