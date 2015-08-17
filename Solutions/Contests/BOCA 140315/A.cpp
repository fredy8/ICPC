#include <iostream>
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
using namespace std;

int main () {
	ios_base::sync_with_stdio(false);
	int arr[8], valid = true, usedCol = 0, diagLeft = 0, diagRight = 0;

	FOR(i, 0, 8) {
		string line;
		cin >> line;
		arr[i] = -1;
		FOR(j, 0, 8) {
			if (line[j] == '*') {
				if (arr[i] != -1)
					valid = false;
				else
					arr[i] = j;
			}
		}
		if (arr[i] == -1)
			valid = false;
	}

	FOR(i, 0, 8) {
		int bit = 1 << arr[i];
		valid &= !((usedCol | diagLeft | diagRight) & bit);
		if (!valid) break;
		usedCol |= bit;
		diagLeft |= bit, diagLeft <<= 1;
		diagRight |= bit, diagRight >>= 1;
	}

	cout << (valid ? "valid" : "invalid") << endl;
}