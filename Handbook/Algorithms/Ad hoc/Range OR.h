typedef unsigned long long ull;
ull rangeOR(ull A, ull B) {
    ull value = 0;
    for(ull i=1ull << 63; i; i >>= 1) {
        value <<= 1;
        value += A/i&1 || B/i&1 || A/i != B/i;
    }
    return value;
}