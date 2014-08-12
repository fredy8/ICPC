#define ANY
int binarySearch(int array[], int searchValue, int left, int right) {
    int leftBound = left, rightBound = right;
    while(left <= right) {
        int mid = (left+right)>>1;
        if(searchValue > array[mid]) left = mid+1;
        else if (searchValue < array[mid]) right = mid-1;
        else {
            #ifdef UPPERBOUND
                if(mid == rightBound || array[mid+1] != array[mid])
                    return mid;
            left = mid+1;
            #endif
            #ifdef LOWERBOUND
                if(mid == leftBound || array[mid-1] != array[mid])
                    return mid;
            right = mid-1;
            #endif
            #ifdef ANY
                return mid;
            #endif
        }
    }
    return -1;
}