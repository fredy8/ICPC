//max 25
long long fact(int n) {
	long long res = 1;
	FOR(i, 2, n+1) res*=i;
	return res;
}

int nCr(long long n, long long r) {
	long long res = 1;
	for(int i=0; i>=1-r; i--) 
		res *= n + i;
	return res/fact(r);
}

#define MAXN 68
long long pascal[MAXN][MAXN];
void buildPascal() {
	FOR(n, 0, MAXN)
		FOR(r, 0, n+1)
			pascal[n][r] = (r == 0 || r == n) ? 1 : pascal[n-1][r-1] + pascal[n-1][r];
}