int factmod (int n, int p) {
	int res = 1;
	while(n > 1) {
		res = (res * modpow (p-1, n/p, p)) % p;
		for(int i = 2; i <= n%p; i++)
			res = (res * i) % p;
		n /= p;
	}
	return res % p;
}