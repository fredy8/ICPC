/*
2100000000
2100000000
2100000000
2100000000
2100000000
2100000000
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

	multiset<long long> s;
	long long n;
	cin >> n;
	s.insert(n);

	multiset<long long>::iterator median = s.begin();
	cout << *median << endl;

	while(cin >> n) {
		s.insert(n);
		if(s.size()%2 == 0) {
			if(n < *median) {
				median--;
			}
			cout << (*(++median) + *(--median))/2 << endl;
		} else {
			if(n > *median) {
				median++;
			}
			cout << *median << endl;
		}
	}

}