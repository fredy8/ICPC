long long fibn(int n) { //max 91
    double goldenRatio = (1+sqrt(5))/2;
    return round((pow(goldenRatio, n+1) - pow(1-goldenRatio, n+1))/sqrt(5));
}

long long fib[92];
void buildFibonacci() {
    fib[0] = fib[1] = 1;
    for(int i=2; i<=100; i++) fib[i] = fib[i-2] + fib[i-1];
}

long long fibonacci(int n) {
    Matriz m(2, 2);
    m[0][0] = 1, m[0][1] = 1, m[1][0] = 1, m[1][1] = 0;
    Matriz fib0(2, 1);
    fib0[0][0] = 1, fib0[1][0] = 1; //fib0 y fib1
    Matriz r = multiply(pow(m, n), fib0);
    return r[1][0];
}