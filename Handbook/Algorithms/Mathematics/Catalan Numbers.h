
unsigned long long nthCatalan(int n) {
	return 2*fact(n)/(pow(fact(n), 2)*(n+1));
}

unsigned long long nextCatalan(int n, unsigned long long previous) {
	return (2*n+2)*(2*n+1)/((n+1)*(n+1))*previous;
}