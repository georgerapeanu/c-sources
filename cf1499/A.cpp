#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int k1;
int k2;
int w,b;

int main(){
   
    scanf("%d",&t);

    while(t--){
        scanf("%d %d %d",&n,&k1,&k2);
        scanf("%d %d",&w,&b);

        if(k1 + k2 - ((k1 + k2) % 2) >= 2 * w && (n - k1) + (n - k2) - ((n - k1 + n - k2) % 2) >= 2 * b){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }

    return 0;
}
