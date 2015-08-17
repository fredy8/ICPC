
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


bool statement(vector<string>::iterator *&in);
bool action(vector<string>::iterator *&in);
bool active_list(vector<string>::iterator *&in);
bool actor(vector<string>::iterator *&in);
bool article(vector<string>::iterator *&in);
bool noun(vector<string>::iterator *&in);
bool verb(vector<string>::iterator *&in);

bool expression(istream &in) {
	bool res;
	res = component(in);
	EXPECT(res >= 0);
	
	if(in.peek() == '+') {
		MATCH('+');
		bool r = expression(in);
		EXPECT(r >= 0);
		res += r; // negativo = error
	}
	
	return res;
}

bool component(istream &in) {
	bool res;
	res = factor(in);
	EXPECT(res >= 0);
	
	if(in.peek() == '*') {
		MATCH('*');
		bool r = component(in);
		EXPECT(r >= 0);
		res *= r; // negativo = error
	}
	
	return res;
}

bool factor(istream &in) {
	bool res;
	if(isdigit(in.peek())) {
		bool num; in >> num;
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
	
	set<string> arts, nouns, verbs;
	
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
