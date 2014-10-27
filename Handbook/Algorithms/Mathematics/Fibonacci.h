int fibn(int n) { //max 91
	double goldenRatio = (1+sqrt(5))/2;
	return round((pow(goldenRatio, n+1) - pow(1-goldenRatio, n+1))/sqrt(5));
}

int fibonacci(int n) {
	Matrix m = CREATE(2, 2);
	m[0][0] = 1, m[0][1] = 1, m[1][0] = 1, m[1][1] = 0;
	Matrix fib0 = CREATE(2, 1);
	fib0[0][0] = 1, fib0[1][0] = 1; //fib0 y fib1
	Matrix r = multiply(pow(m, n), fib0);
	return r[1][0];
}
