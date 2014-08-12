//d = ax + by
void extendedEuclid(int a, int b, int &x, int &y, int &d) {
    if(!b) { x = 1; y = 0; d = a; return; }
    extendedEuclid(b, a%b, x, y, d);
    int x1 = y;
    int y1 = x - (a/b)*y;
    x = x1, y = y1;
}

//r = ax + by
void extendedEuclidean (int a, int b, int &x, int &y, int &r) {
    int r0 = a, r1 = b, s0 = 1, t0 = 0, s1 = 0, t1 = 1;
    while(r1) {
        int aux, q;
        aux = r1;
        q = r0 / r1;
        r1 = r0 % r1;
        r0 = aux;
        aux = s1;
        s1 = s0 - q * s1;
        s0 = aux;
        aux = t1;
        t1 = t0 - q * t1;
        t0 = aux;
    }
    if(r0 < 0) r0 = -r0, s0 = -s0, t0 = -t0;
    r = r0, x = s0, y = t0;    
}