#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[200005];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }

        int ans = 0;
        int lst = 1;
        int cnt = 1;

        while(true){
            ans++;
            int new_cnt = 0;
            
            while(true){
                lst++;
                new_cnt++;
                while(lst < n && a[lst] < a[lst + 1]){
                    lst++;
                    new_cnt++;
                }
                cnt--;
                if(cnt == 0 || lst == n){
                    break;
                }
            }
            cnt = new_cnt;
            if(lst == n){
                break;
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
