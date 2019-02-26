#include <iostream>

using namespace std;

int main() {

    long long A,B,M;

    cin >> A >> B >> M;

    if(B / M != A / M) {
        cout << M - 1;
    }
    else {
        cout << B % M;
    }

    return 0;
}
