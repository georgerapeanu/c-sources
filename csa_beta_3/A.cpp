#include <iostream>

using namespace std;

int n;
int v[5005];

int main() {

    cin >> n;

    int ma = 0,mi = 1e9;

    for(int i = 1; i <= n; i++) {

        cin >> v[i];

        ma = max(ma,v[i]);

        mi = min(mi,v[i]);

    }



    int ans = 1e9;



    for(int i = 1; i <= n; i++) {

        int tmp_ma = 0,tmp_mi = 1e9;

        for(int j = i; j <= n; j++) {

            tmp_ma = max(tmp_ma,v[j]);

            tmp_mi = min(tmp_mi,v[j]);

            if(tmp_ma == ma && tmp_mi == mi) {

                ans = min(ans,j - i + 1);

            }

        }

    }



    cout << ans;



    return 0;

}
