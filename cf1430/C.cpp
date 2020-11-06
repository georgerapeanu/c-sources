#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;

    scanf("%d",&t);

    while(t--){
        int n;
        scanf("%d",&n);

        if(n == 2){
            printf("2\n1 2\n");
            continue;
        }

        printf("2\n%d %d\n%d %d\n",n - 2,n,n - 1,n - 1);

        for(int i = n - 1;i - 2 >= 1;i--){
            printf("%d %d\n",i - 2,i);
        }

    }

    return 0;
}
