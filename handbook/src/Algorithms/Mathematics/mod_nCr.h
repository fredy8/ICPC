int nCr(int n, int r, int MOD) {
	if (n-r < r)
		return nCr(n, n-r, MOD);
	int res = 1;
	FOR(i, 0, r) {
		res = res*(n-i)%MOD;
		res = res*mod_inverse(i+1, MOD)%MOD;
	}
	return res;
}