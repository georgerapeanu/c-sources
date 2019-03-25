#include <bits/stdc++.h>

using namespace std;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int x,y;

int main() {
    cin >> x >> y;
    int dir = 1;

    string command;
    int steps;

    while(cin >> command >> steps) {
        if(command == "F") {
            x += dx[dir] * steps;
            y += dy[dir] * steps;
        }
        else {
            dir += steps;
            dir %= 4;
        }
    }

    cout << x << " " << y;

    return 0;
}
