#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    scanf("%d",&t);

    while(t--){
        int l,r;
        scanf("%d %d",&l,&r);

        printf(l * 2 > r ? "YES\n":"NO\n");
    }

    return 0;
}
