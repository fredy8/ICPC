/* Maximum Subarray
*/
int maximumSubarray(int numbers[], int N) {
	int maxSoFar = numbers[0], maxEndingHere = numbers[0];
	FOR(i, 1, N) {
		if(maxEndingHere < 0) maxEndingHere = numbers[i];
		else maxEndingHere += numbers[i];
		maxSoFar = max(maxEndingHere, maxSoFar);
	}
	return maxSoFar;
}
int maxCircularSum (int a[], int n) {
   int max_kadane = maximumSubarray(a, n);
   int max_wrap  =  0;
   FOR(i, 0, n) {
        max_wrap += a[i];
        a[i] = -a[i];
   }
   max_wrap = max_wrap + maximumSubarray(a, n);
   return (max_wrap > max_kadane)? max_wrap : max_kadane;
}
