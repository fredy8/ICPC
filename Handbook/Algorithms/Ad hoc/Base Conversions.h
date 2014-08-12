string toBaseN(long long num, int N) {
    string converted;
    for(long long div=num; div; div /= N) {
        int value = div % N;
        char c = value > 9 ? value + 'A' - 10 : value + '0';
        converted = c + converted;
    }
    return converted;
}

long long toBase10(string num, int b) {
    long long res = 0, k = 1;
    for(int i=num.length()-1; i>=0; i--) {
        char c = toUpper(num[i]);
        int value = c > '9' ? c - 'A' + 10 : c - '0';
        res += (value)*k;
        k*=b;
    }
    return res;
}