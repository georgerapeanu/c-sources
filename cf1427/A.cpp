#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[55];

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        int sum = 0;
        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            sum += a[i];
        }

        sort(a + 1,a + 1 + n);

        if(sum == 0){
            printf("NO\n");
        }
        else{
            printf("YES\n");
            if(sum > 0){
                reverse(a + 1,a + 1 + n);
            }
            for(int i = 1;i <= n;i++){
                printf("%d ",a[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
