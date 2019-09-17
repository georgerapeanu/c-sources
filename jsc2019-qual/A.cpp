#include <bits/stdc++.h>

using namespace std;

int main() {

    int m,d;
    int cnt = 0;
    cin >> m >> d;

    for(int i = 1;i <= m;i++){
        for(int j = 22;j <= d;j++){
            if(j % 10 <= 1){
                continue;
            }
            if((j / 10) * (j % 10) == i){
                cnt++;
            }
        }
    }

    cout << cnt;

    return 0;
}
