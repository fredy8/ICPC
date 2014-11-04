/*
ladder came tape soon leader acme RIDE lone Dreis peat
 ScAlE orb  eye  Rides dealer  NotE derail LaCeS  drIed
noel dire Disk mace Rob dries
#
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

int main() {
	string line;
	vector<pair<map<char, int>, string> > words;
	vector<bool> isAnagram;
	while(cin >> line && line != "#") {
		map<char, int> word;
		FOR(i, 0, line.length()) {
			char c = tolower(line[i]);
			if(word.find(c) == word.end()) {
				word[c] = 1;
			} else {
				word[c]++;
			}
		}
		bool anagram = true;
		FOR(i, 0, words.size())
			if(words[i].first == word) {
				isAnagram[i] = false;
				anagram = false;
			}
		words.pb(make_pair(word, line));
		isAnagram.pb(anagram);
	}

	vector<string> w;
	FOR(i, 0, words.size())
		if(isAnagram[i])
			w.pb(words[i].second);

	sort(w.begin(), w.end());
	FORC(w, it)
		cout << *it << endl;

}