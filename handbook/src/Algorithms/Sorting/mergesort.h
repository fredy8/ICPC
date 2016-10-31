/* Mergesort
*/
int merge(int array[], int low, int mid, int high) {
	int inversions = 0;
	int sorted[high-low+1];
	int p1 = low, p2 = mid+1, psorted = 0;
	while(p1 <= mid && p2 <= high) {
		if(array[p1] <= array[p2])
			sorted[psorted++] = array[p1++];
		else {
			sorted[psorted++] = array[p2++];
			inversions += mid-p1+1;
		}
	}
	while(p1 <= mid) sorted[psorted++] = array[p1++];
	while(p2 <= high) sorted[psorted++] = array[p2++];
	FOR(i, low, high+1) array[i] = sorted[i-low];
	return inversions;
}

//returns the number of inversions
int mergeSort(int array[], int low, int high) {
	if(low < high) {
		int mid = (low + high)/2;
		int inversions = mergeSort(array, low, mid) + mergeSort(array, mid+1, high);
		return inversions + merge(array, low, mid, high);
	}
	return 0;
}
