int toJulian(int day, int month, int year) {
    return 1461 * (year + 4800 + (month - 14) / 12) / 4 +
        367 * (month - 2 - (month - 14) / 12 * 12) / 12 - 
        3 * ((year + 4900 + (month - 14) / 12) / 100) / 4 + 
        day - 32075;
}

void toGregorian(int julian, int &day, int &month, int &year) {
    int x, n, i, j;
    x = julian + 68569;
    n = 4 * x / 146097;
    x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447;
    day = x - 2447 * j / 80;
    x = j / 11;
    month = j + 2 - 12 * x;
    year = 100 * (n - 49) + i + x;
}

bool isLeap(int year) { return year%4 == 0 && year%100 != 0 || year%400 == 0; }