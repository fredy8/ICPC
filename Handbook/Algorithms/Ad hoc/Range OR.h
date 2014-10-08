int rangeOR(int A, int B) {
	int value = 0;
	for(int i= 1<<(sizeof(int)-1); i; i >>= 1) {
		value <<= 1;
		value += A/i&1 || B/i&1 || A/i != B/i;
	}
	return value;
}