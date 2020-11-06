#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int lst_val = 1e9;
int val;

int main(){


    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        bool ok = false;

        lst_val = 1e9 + 5;
        for(int i = 1;i <= n;i++){
            scanf("%d",&val);
            if(lst_val <= val && ok == false){
                printf("YES\n");
                ok = true;
            }
            lst_val = val;
        }
        if(ok == false){
            printf("NO\n");
        }
    }

    return 0;
}
