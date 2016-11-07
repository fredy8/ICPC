/* Linear Suffix Array
  int N = 6, SA[6];
  char S[6] = "abcab";
  SA_IS((unsigned char*)S, SA, N, 256);
  FOR(i, 0, N) cout << S+SA[i] << endl;
*/
#include <unistd.h>

unsigned char mask[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
	int i, sum = 0;
	for (i = 0; i <= K; i++) bkt[i] = 0;
	for (i = 0; i < n; i++) bkt[chr(i)]++;
	for (i = 0; i <= K; i++) {
		sum += bkt[i];
		bkt[i] = end ? sum : sum - bkt[i];
	}
}
void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
	int i, j;
	getBuckets(s, bkt, n, K, cs, end);
	for (i = 0; i < n; i++) {
		j = SA[i] - 1;
		if (j >= 0 && !tget(j))
			SA[bkt[chr(j)]++] = j;
	}
}
void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
	int i, j;
	getBuckets(s, bkt, n, K, cs, end);
	for (i = n - 1; i >= 0; i--) {
		j = SA[i] - 1;
		if (j >= 0 && tget(j)) SA[--bkt[chr(j)]] = j;
	}
}

void SA_IS(unsigned char *s, int *SA, int n, int K, int cs = 1) {
	int i, j;
	unsigned char *t = (unsigned char *) malloc(n / 8 + 1); // LS-type array in bits
	tset(n-2, 0);
	tset(n-1, 1);
	for (i = n - 3; i >= 0; i--)
		tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);
	int *bkt = (int *) malloc(sizeof(int) * (K + 1));
	getBuckets(s, bkt, n, K, cs, 1);
	for (i = 0; i < n; i++) SA[i] = -1;
	for (i = 1; i < n; i++) if (isLMS(i))
		SA[--bkt[chr(i)]] = i;
	induceSAl(t, SA, s, bkt, n, K, cs, 0);
	induceSAs(t, SA, s, bkt, n, K, cs, 1);
	free(bkt);
	int n1 = 0;
	for (i = 0; i < n; i++)
		if (isLMS(SA[i]))
			SA[n1++] = SA[i];
	for (i = n1; i < n; i++)
		SA[i] = -1;
	int name = 0, prev = -1;
	for (i = 0; i < n1; i++) {
		int pos = SA[i];
		bool diff = 0;
		for (int d = 0; d < n; d++)
			if (prev == -1 || chr(pos+d) != chr(prev+d) || tget(pos+d) != tget(prev+d)) {
				diff = 1;
				break;
			} else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d))) break;
		if (diff) {
			name++;
			prev = pos;
		}
		pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
		SA[n1 + pos] = name - 1;
	}
	for (i = n - 1, j = n - 1; i >= n1; i--) if (SA[i] >= 0)
		SA[j--] = SA[i];
	int *SA1 = SA, *s1 = SA + n - n1;
	if (name < n1) SA_IS((unsigned char*) s1, SA1, n1, name - 1, sizeof(int));
	else for (i = 0; i < n1; i++)
		SA1[s1[i]] = i;
	bkt = (int *) malloc(sizeof(int) * (K + 1));
	getBuckets(s, bkt, n, K, cs, true);
	for (i = 1, j = 0; i < n; i++) if (isLMS(i))
		s1[j++] = i;
	for (i = 0; i < n1; i++) SA1[i] = s1[SA1[i]];
	for (i = n1; i < n; i++) SA[i] = -1;
	for (i = n1 - 1; i >= 0; i--) {
		j = SA[i];
		SA[i] = -1;
		SA[--bkt[chr(j)]] = j;
	}
	induceSAl(t, SA, s, bkt, n, K, cs, 0);
	induceSAs(t, SA, s, bkt, n, K, cs, 1);
	free(bkt);
	free(t);
}
