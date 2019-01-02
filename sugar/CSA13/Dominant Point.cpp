#include <iostream>

using namespace std;

int n;
int max_x = 0;
int max_y = 0;
int ok = -1;

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x,y;
        cin >> x >> y;
        if(x > max_x && y > max_y) {
            ok = i;
            max_x = x;
            max_y = y;
        }
        else if(x > max_x) {
            ok = -1;
            max_x = x;
        }
        else if(y > max_y) {
            ok = -1;
            max_y = y;
        }
    }
    cout << ok;
    return 0;
}