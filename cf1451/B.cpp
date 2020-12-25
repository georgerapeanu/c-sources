#include <bits/stdc++.h>

using namespace std;

int t;
int n,q;
bool is_pref[105][2];
bool is_suff[105][2];
string s;

int main(){
    
    cin >> t;

    while(t--){
        cin >> n >> q;
        cin >> s;
        s = " " + s;
        for(int i = 1;i <= n;i++){
            is_pref[i][0] = is_pref[i - 1][0] | (s[i] == '0');
            is_pref[i][1] = is_pref[i - 1][1] | (s[i] == '1');
        }
        is_suff[n + 1][0] = is_suff[n + 1][1] = false;
        for(int i = n;i;i--){
            is_suff[i][0] = is_suff[i + 1][0] | (s[i] == '0');
            is_suff[i][1] = is_suff[i + 1][1] | (s[i] == '1');
        }
        while(q--){
            int l,r;
            scanf("%d %d",&l,&r);
            if(r - l + 1 < 2){
                printf("NO\n");
            }
            else if(is_pref[l - 1][s[l] - '0'] || is_suff[r + 1][s[r] - '0']){
                printf("YES\n");
            }
            else{
                printf("NO\n");
            }
        }
    }

    return 0;
}
