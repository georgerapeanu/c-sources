#include <bits/stdc++.h>

using namespace std;

int n;
int ans[1005][1005];

int main() {
    cin >> n;
    int last = 0;
    for(int i = 1;i <= n / 2;i++){
        for(int j = 1;j <= n / 2;j++){
            ans[i][j] = last;
            ans[i][j + n / 2] = last + 1;
            ans[i + n / 2][j] = last + 2;
            ans[i + n / 2][j + n / 2] = last + 3;
            last += 4;
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
