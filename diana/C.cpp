#include <bits/stdc++.h>

using namespace std;

int f(int n){
    vector<int> fr(10);
    for(int i = 1;i <= n;i *= 10){
        fr[(n / i) % 10]++;
    }
    int ans = 0;
    for(auto it:fr){
        ans += (it != 0);
    }
    return ans;
}

int main(){
    int n = 5 << 7;
    int ans = 1e9;
    int where = 0;

    for(int k = n;k <= 1e9;k += n){
        if(f(k) < ans){
            ans = f(k);
            where = k;
        }
    }

    printf("%d %d %d\n",ans,where,where / n);
}
