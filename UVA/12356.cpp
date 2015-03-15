#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cctype>

using namespace std;

typedef pair<int, int> ii;

ii sp[100002];

int main() {
	
	int S, B;
	
	while(cin >> S >> B, S || B) {
		for(int i = 1; i <= S; i++) {
			sp[i].first = i - 1;
			sp[i].second = i + 1;
		}
		
		while(B--) {
			int lo, hi;
			
			cin >> lo >> hi;
			
			int l, r;
			l = sp[lo].first;
			r = sp[hi].second;
	
			if(l == 0) cout << "*";
			else cout << l;
			cout << " ";
			if(r == S+1) cout << "*";
			else cout << r;
			cout << endl;
			
			sp[l].second = r;
			sp[r].first = l;
		}
		
		cout << "-" << endl;
	}
}

