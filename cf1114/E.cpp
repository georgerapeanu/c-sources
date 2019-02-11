#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int n;
pair<int,int> perm[1000005];
int vals[1000005];
int gcd(int a,int b) {
    if(!b) {
        return a;
    }
    return gcd(b, a % b);
}

int great(int a) {
    int ans;
    cout << "> " << a << endl;
    cin >> ans;
    return ans;
}

int get(int x) {
    int ans;
    cout << "? " << x << endl;
    cin >> ans;
    return ans;
}

int main() {

    srand(time(NULL));

    cin >> n;

    int xn = 0;

    for(int shift = 1 << 30; shift; shift >>= 1) {
        if(xn + shift <= 1e9 && great(xn + shift)) {
            xn += shift;
        }
    }

    xn++;

    for(int i = 1; i <= n; i++) {
        perm[i].second = i;
        perm[i].first = rand();
    }

    sort(perm + 1,perm + 1 + n);

    int d = 0;

    for(int i = 1; i <= 30 && i <= n; i++) {
        int ans;
        cout << "? " << perm[i].second << endl;
        cin >> vals[i];
    }

    sort(vals + 1,vals + 1 + min(30,n));

    for(int i = 2; i <= 30 && i <= n; i++) {
        d = gcd(d,vals[i] - vals[i - 1]);
    }

    cout << "! " << xn - (n - 1) * d << " " << d << endl;

    return 0;
}
