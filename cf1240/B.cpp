#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n;
int a[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        
        for(int i = 0;i <= n;i++){
            fst[i] = lst[i] = 0;
        }
        
        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            if(fst[a[i]] == 0){
                fst[a[i]] = i;
            }
            lst[a[i]] = i;
        }

        int len = 0;
        int lst_val = 0;
        int ans = 0;
        int cnt = 0;

        for(int i = 1;i <= n;i++){
            if(lst[i] == 0){
                continue;
            }
            cnt++;
            len = 1 + (lst[lst_val] < fst[i] ? len:0);
            lst_val = i;
            ans = max(ans,len);
        }

        ans = cnt - ans;

        printf("%d\n",ans);
    }

    return 0;
}
