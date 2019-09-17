#include <iostream>

using namespace std;

long long n,x,y;

bool ask(long long x,long long y) {
    if(x < 1 || x > n || y < 1 || y > n) {
        return false;
    }
    string ans;
    cout << "examine " << x << " " << y << endl;
    cin >> ans;
    return (ans == "true");
}

void answer(long long x,long long y) {
    cout << "solution " << x << " " << y << endl;
}

int main() {
    cin >> n >> x >> y;

    long long delta = 1;

    while(ask(x,y + delta) == true) {
        delta *= 2;
    }

    delta /= 2;

    for(; delta; delta /= 2) {
        if(ask(x,y + delta) == true) {
            y += delta;
        }
    }

    delta = 1;
    while(ask(x + delta,y) == true) {
        delta *= 2;
    }

    delta /= 2;

    for(; delta; delta /= 2) {
        if(ask(x + delta,y) == true) {
            x += delta;
        }
    }

    delta = 1;
    while(ask(x - delta,y) == true) {
        delta *= 2;
    }

    delta /= 2;

    long long m = 0;

    for(; delta; delta /= 2) {
        if(ask(x - m - delta,y) == true) {
            m += delta;
        }
    }

    m++;

    x -= (m / 2);
    y -= (m / 2);

    while(ask(x - m,y - m)) {
        x -= m;
        y -= m;
    }

    while(ask(x - 2 * m,y)) {
        x -= 2 * m;
    }

    while(ask(x,y - 2 * m)) {
        y -= 2 * m;
    }

    x += 2 * m;
    y += 2 * m;

    answer(x,y);

    return 0;
}
