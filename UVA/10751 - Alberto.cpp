#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double sq2 = sqrt(2);

double solve(int n)
{
    double r = (n>1 ? n-2 : 0);
    r = r*r*sq2;
    r += (n-1)*4;
    return r;
}

int main()
{
    int T;
    cin >> T;
    cout << fixed << setprecision(3);
    while (T--) {
        int n;
        cin >> n;
        cout << solve(n) << endl;
    }
}
