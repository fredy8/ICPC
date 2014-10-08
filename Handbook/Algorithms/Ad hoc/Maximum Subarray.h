int maximumSubarray(int numbers[], int N) {
    int maxSoFar = numbers[0], maxEndingHere = numbers[0];
    FOR(i, 1, N) {
        if(maxEndingHere < 0) maxEndingHere = numbers[i];
        else maxEndingHere += numbers[i];
        maxSoFar = max(maxEndingHere, maxSoFar);
    }
    return maxSoFar;
}