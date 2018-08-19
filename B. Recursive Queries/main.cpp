#include <iostream>

using namespace std;
int Q;
int f[int(1e6) + 6];
int g[int(1e6) + 6];
int fr[int(1e6) + 6][10];
int main()
{
    f[0] = 1;
    for(int i = 1;i <= 1e6;i++){
        f[i] = (i % 10 ? (i % 10) * f[i / 10] : f[i / 10]);
        g[i] = (i < 10 ? i : g[f[i]]);
        for(int j = 0;j < 10;j++){
            fr[i][j] = fr[i - 1][j];
        }
        fr[i][g[i]]++;
    }
    cin >> Q;
    while(Q--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << fr[r][k] - fr[l - 1][k] << "\n";
    }
    return 0;
}
