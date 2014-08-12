//array must be shuffled before sorting
void quickSort(int arr[], int left, int right) {
    int pivot = arr[(left+right)/2];
    int i = left, j = right;
    while(i <= j) {
        while(arr[i] < pivot) i++;
        while(arr[j] > pivot) j--;
        if(i<=j) swap(arr[i++], arr[j--]);
    }
    if(left < j) quickSort(arr, left, j);
    if(i < right) quickSort(arr, i, right);
}