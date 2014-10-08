string toBaseN(int num, int N) {
    string converted = num ? "" : "0";
    for(int div=abs(num); div; div /= N) {
        int value = div % N;
        converted = char(value > 9 ? value + 'A' - 10 : value + '0') + converted;
    }
    return converted;
}