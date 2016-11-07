/* GCD
*/
int gcd(int a, int b) {
	int tmp;
	while(b){a%=b; tmp=a; a=b; b=tmp;}
	return a;
}

/* LCM
*/
int lcm(int a, int b) {
	return a/gcd(a,b)*b;
}

/* Extended Euclid
Finds x,y such that d = ax + by.
Returns d = gcd(a,b).
*/
int extended_euclid(int a, int b, int &x, int &y) {  
	int xx = y = 0;
	int yy = x = 1;
	while (b) {
		int q = a/b;
		int t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

/* Modular Linaer Equation Solver
Finds all solutions to ax = b (mod n)
*/
vi modular_linear_equation_solver(int a, int b, int n) {
	int x, y;
	vi solutions;
	int d = extended_euclid(a, n, x, y);
	if (!(b%d)) {
		x = mod (x*(b/d), n);
		FOR(i, 0, d)
			solutions.pb(mod(x + i*(n/d), n));
	}
	return solutions;
}

/* Modular Inverse
Computes b such that ab = 1 (mod n), returns -1 on failure
*/
int mod_inverse(int a, int n) {
	int x, y;
	int d = extended_euclid(a, n, x, y);
	if (d > 1) return -1;
	return mod(x,n);
}

/* Chinese Remainder Theorem
Returns \[x = a_i (mod n_i)\]
n's must be pairwise coprimes
*/
int chinese_remainder(int *n, int *a, int len) {
	int p, i, prod = 1, sum = 0;
	for (i = 0; i < len; i++) prod *= n[i];
	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mod_inverse(p, n[i]) * p;
	}
	return sum % prod;
}
