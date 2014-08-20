/*
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
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
	int N;
	while(cin >> N && N != -1) {
		cout << "Round " << N << endl;
		string actual, guessed;
		cin >> actual >> guessed;
		set<char> actualSet;
		FORC(actual, it) {
			actualSet.insert(*it);
		}

		set<char> guessedLetters;
		int errors = 0;
		FORC(guessed, it) {
			if(guessedLetters.find(*it) == guessedLetters.end()) {
				guessedLetters.insert(*it);
				if(actualSet.find(*it) != actualSet.end()) {
					actualSet.erase(actualSet.find(*it));
					if(actualSet.size() == 0)
						break;
				} else {
					errors++;
					if(errors == 7) {
						break;
					}
				}
			}
		}

		if(actualSet.size()) {
			if(errors == 7) {
				cout << "You lose." << endl;
			} else {
				cout << "You chickened out." << endl;
			}
		} else {
			cout << "You win." << endl;
		}
	}
}