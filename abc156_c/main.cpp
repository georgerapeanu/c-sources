#include <iostream>

using namespace std;

int n;
int x[105];

int main(){

    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> x[i];
    }

    int ans = 1e9;

    for(int p = 0;p <= 100;p++){
        int tmp = 0;

        for(int i = 1;i <= n;i++){
            tmp += (x[i] - p) * (x[i] - p);
        }
        ans = min(ans,tmp);
    }

    cout << ans;

    return 0;
}
