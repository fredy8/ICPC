// returns x = a_i (mod n_i)
// n's must be pairwise coprimes
int chinese_remainder(int *n, int *a, int len) {
	int p, i, prod = 1, sum = 0;
	for (i = 0; i < len; i++) prod *= n[i];
	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mod_inverse(p, n[i]) * p;
	}
	return sum % prod;
}
