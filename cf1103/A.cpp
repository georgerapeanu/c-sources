#include <iostream>
#include <vector>

using namespace std;

string s;

bool viz[5][5];
bool okl[5];
bool okc[5];

int main() {

    cin >> s;

    for(auto it:s) {
        if(it == '0') {
            if(!viz[3][4]) {
                cout << 3 << " " << 4 << "\n";
                viz[3][4] = true;
            }
            else {
                cout << 1 << " " << 4 << "\n";
                viz[3][4] = false;
            }
        }
        else {
            if(!viz[1][1]) {
                cout << 1 << " " << 1 << "\n";
                viz[1][1] = true;
            }
            else {
                cout << 1 << " " << 3 << "\n";
                viz[1][1] = false;
            }
        }
    }

    return 0;
}
