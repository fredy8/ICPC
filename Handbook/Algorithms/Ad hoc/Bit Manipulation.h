#define bits(a) __builtin_popcount(a)
#define toggleBit(n, b) ((n) ^= (p2((b))))
#define LSB(n) ((n) & (-(n)))
//returns nearest power of two, choose the bigger one if both have the same difference
#define turnOffLastBit(S) ((S) & (S - 1))
#define turnOnLastZero(S) ((S) | (S + 1))
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S - 1))

int MSB(int x) {
    if(!x) return 0;
    int ans = 1;
    while(x>>1) x>>=1, ans<<=1;
    return ans;
}