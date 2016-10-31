const int UPPERBOUND = 0, LOWERBOUND = 1, ANY = 2;
int binarySearch(int array[], int searchValue, int left, int right, int type = ANY) {
	int leftBound = left, rightBound = right;
	while(left <= right) {
        int mid = (left+right)/2;
		if(searchValue > array[mid]) left = mid+1;
		else if (searchValue < array[mid]) right = mid-1;
		else {
            if(type == UPPERBOUND) {
                if(mid == rightBound || array[mid+1] != array[mid])
                    return mid;
                left = mid+1;
            } else if(type == LOWERBOUND) {
                if(mid == leftBound || array[mid-1] != array[mid])
                    return mid;
                right = mid-1;
            } else {
                return mid;
            }
		}
	}
	return -1;
}
