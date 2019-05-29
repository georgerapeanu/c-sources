#include <iostream>

using namespace std;

int n;
string s;

int main() {

    cin >> n;
    cin >> s;

    int cntA = 0;
    int xo = 0;
    int len_b = 0;

    for(auto it:s) {
        if(it == 'A') {
            cntA++;
            xo ^= len_b;
            len_b = 0;
        }
        else if(it == 'B') {
            len_b++;
        }
    }

    xo ^= len_b;

    if(xo == 0) { ///b wins game on b's
        if(cntA % 2 == 0) {
            cout << -1;
        }
        else {
            cout << 'B';
        }
    }
    else {
        if(cntA % 2 == 0) {
            cout << -1;
        }
        else {
            cout << 'A';
        }
    }
    return 0;
}
