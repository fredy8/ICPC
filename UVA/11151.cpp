#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
	//char tbl[1000];
	string s;
	int lps[1001][1001];
	int c;
	for(cin >> c, cin.ignore(); c--;) {
		//cin >> s;
		getline(cin, s);
		
		memset(lps, 0, sizeof lps); 
		
		for(int l = 1; l <= s.size(); l++) {
			for(int i = 0; i <= s.size() - l; i++) {
				int j = i + l - 1;
				if(s[i] == s[j]) {
					lps[i][j] = 2 + lps[i + 1][j - 1];
					if(l == 1) lps[i][j]--; // branch prediction fails only once
				} else {
					lps[i][j] = max(lps[i][j - 1], lps[i + 1][j]);
				}
			}
		}
		
		/*for(int i = 0; i < s.size(); i++) {
			for(int j = 0; j < s.size(); j++) {
				cout << lps[i][j] << " ";
			}
			cout << endl;
		}*/
		
		cout << lps[0][s.size() - 1] << endl;
	}
}
