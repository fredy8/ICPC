//max n=61
int nCr(int n, int r) {
	int res = 1;
	FOR(i, 0, r) res = res*(n-i)/(i+1);
	return res;
}

#define MAXN 68
long long pascal[MAXN][MAXN];
void buildPascal() {
	FOR(n, 0, MAXN)
		FOR(r, 0, n+1)
			pascal[n][r] = (r == 0 || r == n) ? 1 : pascal[n-1][r-1] + pascal[n-1][r];
}
