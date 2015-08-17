/*
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255
255

*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
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
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

char output(int n) {
	switch(n) {
		case 0: return '!';
		case 1: return '@';
		case 2: return '#';
		case 3: return '$';
		case 4: return '%';
		case 5: return '&';
		default: return n - 6 + 'a';
	};
}

int fromBinary(string num) {
	int n = 0;
	FOR(i, 0, num.length()) {
		n *= 2;
		n += num[i]-'0';
	}
	return n;
}

string toBinary(int n) {
	string num = "";
	FOR(i, 0, 8) {
		num = (char)(n%2 + '0') + num;
		n /= 2;
	}
	return num;
}

mint main() {
	ios_base::sync_with_stdio(false);
	int n, s = 0;
	string acum = "", result = "";
	while (cin >> n) {
		acum += toBinary(n);
		while (acum.length() >= 5) {
			string binary = acum.substr(0, 5);
			acum = acum.substr(5);
			cout << output(fromBinary(binary));
			s++;
			if (s%80 == 0) cout << endl;
		}
	}
	if (acum.length()) {
		while (acum.length() < 5) {
			acum += '0';
		}
		while (acum.length() >= 5) {
			string binary = acum.substr(0, 5);
			acum = acum.substr(5);
			cout << output(fromBinary(binary));
			s++;
			if (s%80 == 0) cout << endl;
		}
	}
	if (s%80) cout << endl;
	return 0;
}