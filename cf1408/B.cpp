#include <bits/stdc++.h>

using namespace std;

int t;
int n,k;
int a[105];

int main() {
    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        int cnt = 1;

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            cnt += (i > 1 && a[i] != a[i - 1]);
        }

        if(cnt <= k){
            printf("%d\n",1);
        }
        else if(k == 1){
            printf("-1\n");
        }
        else{
            printf("%d\n",(cnt - 1 + k - 2) / (k - 1));
        }
    }
    


    return 0;
}
