#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cctype>
#include <unordered_map>

using namespace std;

int main() {
	string s;
	
	while(getline(cin, s), s != "DONE") {
		bool read = true;
		long long i = 0, j = (long long)s.size() - 1;
		while(i <= j) {
			if(!isalpha(s[i])) i++;
			else if(!isalpha(s[j])) j--;
			else {
					read = true;
				if(toupper(s[i]) != toupper(s[j])) {
					j = -2;
				} else {
					i++;
					j--;
				}
			}
		}
		if(read) {
			if(j != -2)
				cout << "You won't be eaten!" << endl;
			else
				cout << "Uh oh.." << endl;
		} else {
			cout << "Uh oh.." << endl;
		}
	}
	
	
}
