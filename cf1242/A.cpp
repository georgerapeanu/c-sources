#include <bits/stdc++.h>
#include <cmath>

using namespace std;

long long n;

int main() {

    cin >> n;

    int p = -1,e = 0;

    for(int i = 2; 1LL * i * i <= n; i++) {
        if(n % i == 0) {
            p = i;
            e = 0;
            while(n % i == 0) {
                e++;
                n /= i;
            }
            if(n != 1) {
                cout << "1\n";
                return 0;
            }
            else {
                cout << i << "\n";
                return 0;
            }
        }
    }

    cout << n << "\n";

    return 0;
}
