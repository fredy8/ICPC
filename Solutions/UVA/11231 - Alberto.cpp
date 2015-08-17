#include <iostream>
using namespace std; 
typedef long long ll; 

ll solve(int n, int m, bool sq)
{
    int t = 0;
    t += ((m-6-!sq)/2)*((n-6)/2);
    t += ((m-6-sq)/2)*((n-7)/2);
    return t;
}

int main()
{
    int n, m;
    bool sq;
    while (cin >> n >> m >> sq && n) {
        cout << solve(n, m, sq) << endl;
    }
}
