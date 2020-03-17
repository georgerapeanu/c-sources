#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int t,n;

int a[105];
int b[105];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }
        for(int i = 1;i <= n;i++){
            scanf("%d",&b[i]);
        }

        sort(a + 1,a + 1 + n);
        sort(b + 1,b + 1 + n);

        for(int i = 1;i <= n;i++){
            printf("%d ",a[i]);
        }
        printf("\n");
        for(int i = 1;i <= n;i++){
            printf("%d ",b[i]);
        }
        printf("\n");
    }

    return 0;
}
