#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}


int cd(int n) {
	int  count =0;
	
	while(n!=0)
  {
      n/=10;  
      ++count;
  }
  
  return count;
}

int main() {
	int c = 1;
	for(int n; cin >> n, n; c++) {
		
		cout << "Case " << c << ":" << endl;
		int suma = 0;
		for(int i = 0; i < n; i++) {
			int x;
			cin >> x;
			suma += x;
		}
		bool neg = suma < 0;
		suma = neg ? -suma : suma;
		
		int ent = suma / n;
		int num = suma % n;
		int den = n;
		int g = gcd(num, den);
		num /= g;
		den /= g;
		
		int ndigs = cd(num), ddigs = cd(den), edigs = cd(ent);
		
		//cout << "CASE " << (neg ? "-" : "") << ent << " " << num << "/" << den << endl;
		//cout << "NDIG " << edigs << " " << ndigs << "/" << ddigs << endl;

		
		int izq = 0;
		
		if(neg) izq += 2;
		izq += edigs;
		
		if(num) {
			for(int x = 0; x < izq; x++) cout << " ";
			for(int x = ndigs; x < ddigs; x++) cout << " ";
			cout << num;
			cout << endl;
		}
		
		if(neg) {
			cout << "- ";
		}
		
		if(ent || !num) {
			cout << ent;
		}
		
		if(num) {
			for(int i = 0; i < ddigs; i++) {
				cout << "-";
			}
		}
		
		cout << endl;
		
		if(num) {
			for(int x = 0; x < izq; x++) cout << " ";
			cout << den << endl;
		}
	}
}
