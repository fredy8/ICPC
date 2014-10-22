int mod(int a, int b) {
	return ((a%b)+b)%b;
}

int modpow(int base, int exp, int modulus) {
	base = mod(base, modulus);
	int result = 1;
	while (exp) {
		if (exp & 1) result = mod(result * base, modulus);
		base = mod(base * base, modulus);
		exp >>= 1;
	}
	return result;
}