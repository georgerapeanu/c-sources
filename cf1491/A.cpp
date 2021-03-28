#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n,q;
int v[NMAX + 5];
int cnt[2];

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]); 
        cnt[v[i]]++;
    }

    while(q--){
        int t,x;
        scanf("%d %d",&t,&x);

        if(t == 1){
            cnt[v[x]]--;
            v[x] ^= 1;
            cnt[v[x]]++;
        }else{
            printf("%d\n",(x <= cnt[1]));
        }
    }

    return 0;
}
