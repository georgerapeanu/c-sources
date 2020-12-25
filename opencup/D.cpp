#include <bits/stdc++.h>

using namespace std;

int n;
int x;
int a[100005];
int b[100005];

int main(){

    while(cin >> n){
        cin >> x;
        for(int i = 1;i <= n;i++){
            cin >> a[i];
        }
        for(int i = 1;i <= n;i++){
            cin >> b[i];
        }

        int pw = 1;

        for(int i = 1;i < n;i++){
            pw = 1LL * pw * x % ((int)1e9 + 7);
        }

        int sum = x;

        for(int i = 1;i <= n;i++){
            sum = (sum + 1LL * a[i] * b[i]) % ((int)1e9 + 7);
        }

        sum = (1LL * sum * pw) % ((int)1e9 + 7);

        printf("%d\n",sum);
    }

    return 0;
}
