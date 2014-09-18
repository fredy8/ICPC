#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;

#define PRIME 0x1
#define SEMIPRIME 0x2

int hiscomp[250001];
int hp[250001];
int hpc;


int tree[250001];

int read(int idx){
	int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}
void update(int idx){
	while (idx <= 250001){
		tree[idx]++;
		idx += (idx & -idx);
	}
}

int main() {
	
	for(int a = 5; a < 1001; a += 4) {
		if(!hiscomp[a / 4]) {
			for(int p = a * a; p <= 1000001; p += a) {
				
				if(p < 100) cout << "composite " << p << endl;
				hiscomp[p / 4]++;
			}
		}
	}
	
	for(int i = 0; i < 1001; i++) {
		if(!hiscomp[i])
			cout << (4*i+1) << endl;
		
	}
	
	for(int num = 5; num < 1001; num += 4) {
		if(!hiscomp[num / 4]) {
			hp[hpc++] = num;
			for(int j = 0; j < hpc; j++) {
				//hsp[hspc++] = num * hp[j];
				int semiprime = num * hp[j];
				
				if(semiprime <= 789) 
					cout << "semi " << semiprime
						<< " = " << hp[j] << " * " << num << endl;
				
				update(semiprime / 4);
			}
		}
	}
	
	for(int n; cin >> n, n;) {
		cout << n << " " << read(n / 4) << endl;
	}
}
