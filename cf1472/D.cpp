#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n;
int v[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
        }

        sort(v + 1,v + 1 + n);
        reverse(v + 1,v + 1 + n);

        long long diff = 0;

        for(int i = 1;i <= n;i++){
            diff += ((((i - 1) ^ v[i]) & 1) == 0) * v[i] * (i % 2 == 1 ? 1:-1);
        }
        if(diff < 0){
            printf("Bob\n");
        }else if(diff == 0){
            printf("Tie\n");
        }else{
            printf("Alice\n");
        }
    }

    return 0;
}
