insertionSort(int arr[], int N) {
	FOR(i, 1, N)
		for(int j=i; j && arr[j] < arr[j-1]; j--)
			swap(arr[j], arr[j-1]);
}
