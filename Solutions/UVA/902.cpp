#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
	
	int l;
	string s;
	
	while(cin >> l >> s) {
		unordered_map<string, int> m;
		for(int i = 0; i <= s.size() - l; i++) {
			//cout << "-" << s.substr(i, l) << endl;
			m[s.substr(i, l)]++;
		}
		
		int lm = 0;
		string sm;
	
		for(auto it = m.begin(); it != m.end(); it++) {
			if(it->second > lm) {
				lm = it->second;
				sm = it->first;
			}
		}
	
		cout << sm << endl;
	}
	
	
}
