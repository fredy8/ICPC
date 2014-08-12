#define bits(a) __builtin_popcount(a) //quick bit count on unsigned int
#define isOn(n, b) (((n) & (p2(b))) != 0) //checks if bit b is on
#define setBit(n, b) ((n) |= p2(b)) //sets bit b on n
#define clearBit(n, b) ((n) &= ~(p2((b)))) //clears bit b on n
#define toggleBit(n, b) ((n) ^= (p2((b)))) //toggles bit b on n
#define LSB(n) ((n) & (-(n))) //returns the least significant bit that is on
#define setAll(n, b) ((n) = p2(b) - 1) //sets n to b ones

#define modulo(x, N) ((x) & (N-1)) //returns x % N, where N is a power of 2
#define isPowerOfTwo(x) (((x) & ((x)-1)) == 0)
//returns nearest power of two, choose the bigger one if both have the same difference
#define nearestPowerOfTwo(x) ((int)pow(2.0, (int)((log((double)x) / log(2.0)) + 0.5)))
#define turnOffLastBit(S) ((S) & (S - 1))
#define turnOnLastZero(S) ((S) | (S + 1))
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S - 1))

void printBin(int N) {
    stack<int> st;
    while (N) st.push(N & 1), N >>= 1;
    while (!st.empty()) printf("%d", st.top()), st.pop();
    printf("\n");
}