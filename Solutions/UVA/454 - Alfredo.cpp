/*
3

carthorse
horse
horse cart
i do not know u
ok i now donut
orchestra
 
a
b
A

carthorse
horse
horse cart
i do not know u
ok i now donut
orchestra
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
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<int, pair<int, int> > point;

bool isEmpty(string line) {
	FORC(line, it) {
		if(*it != ' ' && *it != '\t')
			return false;
	}

	return true;
}

int main() {
	int TC;
	cin >> TC;
	string line;
	getline(cin, line);
	getline(cin, line);

	bool first = true;

	while(TC--) {

		if(!first) {
			cout << endl;
		}

		first = false;

		vector<string> lines;
		vector<map<char, int> > unorderedStrings;
		vector<pair<string, string> > ans;
		
		while(getline(cin, line) && !isEmpty(line)) {
			lines.pb(line);

			map<char, int> unorderedString;

			FORC(line, it) {
				if(*it != ' ') {
					char c = *it;
					//if(c >= 'A' && c <= 'Z')
					//	c = tolower(c);
					unorderedString[c]++;
				}
			}

			FOR(i, 0, unorderedStrings.size())
				if(unorderedString == unorderedStrings[i]) {
					if(line < lines[i])
						ans.pb(make_pair(line, lines[i]));
					else
						ans.pb(make_pair(lines[i], line));
				}

			unorderedStrings.pb(unorderedString);
		}

		sort(ans.begin(), ans.end());

		FORC(ans, it)
			cout << it->first << " = " << it -> second << endl;
	}
}