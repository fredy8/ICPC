/*
H
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

char mirrorArr[] = { 'A', '-', '-', '-', '3', '-', '-', 'H', 'I', 'L', '-', 'J', 'M', '-', 'O', '-', '-', '-', '2', 'T', 'U', 'V', 'W', 'X', 'Y', '5', '1', 'S', 'E', '-', 'Z', '-', '-', '8', '-' };

char mirror(char a) {
	if(a == '0')
		return '0';
	if(a >= '1' && a <= '9')
		return mirrorArr[a-'1'+26];
	return mirrorArr[a-'A'];
}

char palindrome(char a) {
	return a;
}

bool check(string a, char (*fn)(char)) {
	FOR(i, 0, a.size()/2+1)
		if(a[i] != fn(a[a.size()-1-i]))
			return false;

	return true;
}

int main() {
	string line;
	while(cin >> line) {
		cout << line << " -- ";
		if(check(line, &mirror)) {
			if(check(line, &palindrome)) {
				cout << "is a mirrored palindrome." << endl;
			} else {
				cout << "is a mirrored string." << endl;
			}
		} else {
			if(check(line, &palindrome)) {
				cout << "is a regular palindrome." << endl;
			} else {
				cout << "is not a palindrome." << endl;
			}
		}
		cout << endl;
	}
}