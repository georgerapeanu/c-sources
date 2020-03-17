#include <cstdio>
#include <algorithm>

using namespace std;

int n,m;
int fr[1005];
int actual_val[1005];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        fr[val % m]++;
        actual_val[val % m] = val;
    }

    for(int i = 0;i < m;i++){
        if(fr[i] > 1){
            printf("0\n");
            return 0;
        }
    }

    int ans = 1;

    for(int i = 0;i < m;i++){
        if(fr[i] == 0){
            continue;
        }
        for(int j = 0;j < i;j++){
            if(fr[j] == 0){
                continue;
            }
            ans = 1LL * ans * abs(actual_val[i] - actual_val[j]) % m;
        }
    }

    printf("%d\n",ans);

    return 0;
}
