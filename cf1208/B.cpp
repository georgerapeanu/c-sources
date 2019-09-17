#include <bits/stdc++.h>

using namespace std;

map<int,int> fr;
int cnt;

int n;
int a[2005];

int main() {
    
    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> a[i];
        fr[a[i]]++;
        if(fr[a[i]] == 2){
            cnt++;
        }
    }

    int ans = 1 << 30;

    for(int l = 1,r = 1;l <= n;l++){
        fr[a[l]]++;
        if(fr[a[l]] == 2){
            cnt++;
        }
        while(cnt && r <= n){
            fr[a[r]]--;
            if(fr[a[r]] == 1){
                cnt--;
            }
            r++;
        }
        if(cnt > 0){
            break;
        }
        ans = min(ans,r - l - 1);
    }

    fr.clear();
    for(int i = n;i;i--){
        fr[a[i]]++;
        if(fr[a[i]] == 2){
            break;
        }
        ans = min(ans,i - 1);
    }

    cout << ans;

    return 0;
}
