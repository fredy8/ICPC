#include <iostream>
#include <vector>

using namespace std;

typedef pair<int> ii;
typedef vector<ii> vii;

bool cmp(const ii &l, const ii &r) {
	return l.first < r.first 
		|| (l.second == r.second
		&&  l.second > r.second);
}

int main() {
	int n, k;
	cin >> n >> k;
	
	vii is;
	
	for(int i = 0; i < k; i++) {
		int x, y;
		
		cin >> x >> y;
		
		y = x <= y ? y - x : 
		
		is.push(ii(x, y));
	}
	
	sort(is.begin(), is.end(), cmp);
		
	int r = 0, c = 0;
		
	for(int j = 0; j < k; j++) {
		r = 
	}
}
