#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <sstream>

using namespace std;

typedef pair<int, int> ii;



int main() {
	for(int n; cin >> n;) {
		cin.ignore();
		string s;
		getline(cin, s);
		stringstream ss(s);
		vector<int> p;
		int x;
		while(ss >> x) {
			p.push_back(x);
		}
		
		for(int i = 0, carry = 0; i < p.size(); i++) {
			p[i] += carry;
			carry = p[i] * n;
		}
		
		for(int i = 0, carry = 0; i < p.size() - 1; i++) {
			p[i] += carry;
			carry = p[i] * n;
		}
		
		cout << p[p.size() - 2] << endl;
	}
}
