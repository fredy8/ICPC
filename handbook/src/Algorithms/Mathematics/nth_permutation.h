/* Nth Permutation
seq must be sorted
*/
string nthPermutation(string seq, int permNum) {
	if(!seq.length()) return "";
	int f = fact(seq.length() - 1);
	int q = permNum/f, r = permNum%f;
	return seq[q] + nthPermutation(seq.substr(0, q) + seq.substr(q+1), r);
}