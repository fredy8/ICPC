selectionSort(int arr[], int N) {
	int MIN;
	FOR(i, 0, N) {
		MIN=i;
		FOR(j, i+1, N)
			if (arr[j] < arr[MIN])
				MIN=j;
		swap(arr[i],arr[MIN]);
	}
}