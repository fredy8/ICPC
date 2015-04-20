
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
typedef long long ll;

#define EXPECT(expr) if(!(expr)) return -1;
#define MATCH(c) { EXPECT(in.peek() == c); in.ignore();}


ll expression(istream &in);
ll factor(istream &in);
ll component(istream &in);

ll expression(istream &in) {
	ll res;
	res = component(in);
	EXPECT(res >= 0);
	
	if(in.peek() == '+') {
		MATCH('+');
		ll r = expression(in);
		EXPECT(r >= 0);
		res += r; // negativo = error
	}
	
	return res;
}

ll component(istream &in) {
	ll res;
	res = factor(in);
	EXPECT(res >= 0);
	
	if(in.peek() == '*') {
		MATCH('*');
		ll r = component(in);
		EXPECT(r >= 0);
		res *= r; // negativo = error
	}
	
	return res;
}

ll factor(istream &in) {
	ll res;
	if(isdigit(in.peek())) {
		ll num; in >> num;
		res = num;
	} else if(in.peek() == '(') {
		MATCH('(');
		res = expression(in);
		MATCH(')');
	} else return -1;
	
	return res;
}

int main() {
	int n;
	
	cin >> n;
	
	while(n--) {
		string s;
		cin >> s;
		stringstream ss(s);
		ll res = expression(ss);
		if(ss || res < 0) cout << "ERROR" << endl;
		else cout << res << endl;
	}	
	
}
// a b a b a3
