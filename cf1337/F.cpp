#include <bits/stdc++.h>

using namespace std;

int deltas[105];
int deltat[105];

int n;

int fr[105];

int main() {

    cin >> n >> deltas[0] >> deltat[0];

    int lst = 0;

    for(int i = n - 1; i > 2; i--) {
        lst++;
        cout << "+ " << i << endl;
        cin >> deltat[lst] >> deltas[lst];
    }

    lst++;
    cout << "+ " << 1 << endl;
    cin >> deltat[lst] >> deltas[lst];
    lst++;
    cout << "+ " << 2 << endl;
    cin >> deltat[lst] >> deltas[lst];
    lst++;
    cout << "+ " << 1 << endl;
    cin >> deltat[lst] >> deltas[lst];

    for(int i = n; i; i--) {
        deltas[i] -= deltas[i - 1];
        deltat[i] -= deltat[i - 1];
    }

    fr[3] = deltas[n] - deltas[n - 2] - 1;
    fr[2] = deltas[n] / (fr[3] + 1) - 1;

    fr[1] = 0;


    while((fr[1] + 1) * fr[1] / 2 < deltat[n]) {
        fr[1]++;
    }

    fr[4] = (deltas[n - 1] - (fr[1] + 1) * (fr[3] + 1)) / (fr[3] + 1) - (4 < n);

    for(int x = 5; x <= n; x++) {
        fr[x] = (deltas[n - (x - 2)] - fr[x - 4] * fr[x - 3] - fr[x - 3] * (fr[x - 1] + 1)) / (fr[x - 1] + 1) - (x < n);
    }

    cout << "! ";

    for(int i = 1; i <= n; i++) {
        cout << fr[i] << " ";
    }

    cout << endl;

    return 0;
}
