#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        double M, B, D, T;
        cin >> M >> B >> D >> T;
        D -= B*T;
        double x = D*M/B;
        double y = 5.5 - x;
        double d = B*y/sqrt(B*B+M*M) + 0.5;
        if (d < 0) {
            cout << "Max beats the first bicycle" << endl;
        } else {
            int cnt = 0;
            bool crash = false;
            double l = 2*M/sqrt(B*B+M*M);
            while (d >= 0 && cnt < 10 && !crash) {
                cnt++;
                if (d <= 1 || d-l <= 1) {
                    crash = true;
                }
                d -= 2*l;
            }
            if (crash) {
                cout << "Collision with bicycle " << cnt << endl;
            } else {
                cout << "Max crosses safely after bicycle " << cnt << endl;
            }
        }
    }
}
