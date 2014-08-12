double fastPow(double a, int n) {
    if(n == 0) return 1;
    if(n == 1) return a;
    double t = fastPow(a, n>>1);
    return t*t*fastPow(a, n&1);
}