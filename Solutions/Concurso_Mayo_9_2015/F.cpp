/*
3 2
10 2 2 3
10 2 1 3
10 2 1 2
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
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

typedef vector<vector<int> > Matrix;
#define EPS 1E-7
#define CREATE(R, C) Matrix(R, vector<int>(C));

Matrix identity(int n) {
	Matrix m = CREATE(n, n);
	FOR(i, 0, n)
		m[i][i] = 1;
	return m;
}

Matrix multiply(Matrix m, double k) {
	FOR(i, 0, m.size())
		FOR(j, 0, m[0].size())
			m[i][j] *= k;
	return m;
}

#define MOD 1000000007

Matrix multiply(Matrix m1, Matrix m2) {
	Matrix result = CREATE(m1.size(), m2[0].size());
	if(m1[0].size() != m2.size())
		return result;
	FOR(i, 0, result.size())
		FOR(j, 0, result[0].size())
			FOR(k, 0, m1[0].size())
				result[i][j] = (result[i][j] + m1[i][k]*m2[k][j]) % MOD;
	return result;
}

Matrix pow(Matrix m, int exp) {
	if(!exp) return identity(m.size());
	if(exp == 1) return m;
	Matrix result = identity(m.size());
	while(exp) {
		if(exp & 1) result = multiply(result, m);
		m = multiply(m, m);
		exp >>= 1;
	}
	return result;
}

//solves AX=B, output: A^-1 in A, X in B, returns det(A)
double gaussJordan(Matrix &a, Matrix &b) {
	int n = a.size(), m = b[0].size();
	vi irow(n), icol(n), ipiv(n);
	double det = 1;
	FOR(i, 0, n) {
		int pj = -1, pk = -1;
		FOR(j, 0, n) if (!ipiv[j])
			FOR(k, 0, n) if (!ipiv[k])
				if (pj == -1 || abs(a[j][k]) > abs(a[pj][pk])) { pj = j; pk = k; }
		if (abs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
		ipiv[pk]++;
		swap(a[pj], a[pk]);
		swap(b[pj], b[pk]);
		if (pj != pk) det *= -1;
		irow[i] = pj;
		icol[i] = pk;

		double c = 1.0 / a[pk][pk];
		det *= a[pk][pk];
		a[pk][pk] = 1.0;
		FOR(p, 0, n) a[pk][p] *= c;
		FOR(p, 0, m) b[pk][p] *= c;
		FOR(p, 0, n) if (p != pk) {
			c = a[p][pk];
			a[p][pk] = 0;
			FOR(q, 0, n) a[p][q] -= a[pk][q] * c;
			FOR(q, 0, m) b[p][q] -= b[pk][q] * c;      
		}
	}
	for(int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
		FOR(k, 0, n) swap(a[k][irow[p]], a[k][icol[p]]);
	}
	return det;
}

//returns the rank of a
int rref(Matrix &a) {
	int n = a.size(), m = a[0].size();
	int r = 0;
	FOR(c, 0, m) {
		int j = r;
		FOR(i, r+1, n)
			if (abs(a[i][c]) > abs(a[j][c])) j = i;
		if (abs(a[j][c]) < EPS) continue;
		swap(a[j], a[r]);
		double s = 1.0 / a[r][c];
		FOR(j, 0, m) a[r][j] *= s;
		FOR(i, 0, n) if (i != r) {
			double t = a[i][c];
			FOR(j, 0, m) a[i][j] -= t * a[r][j];
		}
		r++;
	}
	return r;
}

mint main() {
	int N, K;
	while(cin >> N >> K) {
		Matrix A = CREATE(N, N);
		Matrix B = CREATE(N, 1);
		FOR(i, 0, N) {
			scanf("%lld", &B[i][0]);
			int k;
			scanf("%lld", &k);
			FOR(u, 0, k) {
				int b;
				scanf("%lld", &b);
				A[i][b-1]++;
			}
		}

		Matrix ans = multiply(pow(A, K), B);
		FOR(i, 0, ans.size())
			printf("%lld\n", ans[i][0]);
	}
}