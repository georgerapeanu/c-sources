#include <bits/stdc++.h>

using namespace std;

int t,n;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        if(n <= 3){
            printf("%d\n",n - 1);
        }
        else{
            printf("%d\n",2 + (n % 2 == 1));
        }
    }

    return 0;
}
