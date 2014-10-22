//seq must be sorted
string nthPermutation(string seq, long long permNum) {
	if(!seq.length())
		return "";
	long long f = fact(seq.length() - 1);
	int q = permNum / f;
	long long r = permNum % f;
	return seq[q] + nthPermutation(seq.substr(0, q) + seq.substr(q+1), r);
}