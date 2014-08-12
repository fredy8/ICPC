// Regresa cuantas veces subseq es subsequence de seq
int subseqCounter(string seq, string subseq)
{
    int n = seq.length(), m = subseq.length();
    vi sub(m, 0);
    FOR(i, 0, n)
        for(int j = m-1; j >= 0; j--)
            if(seq[i] == subseq[j])
                if(j == 0) sub[0]++;
                else sub[j] += sub[j-1];
    return sub[m-1];
}