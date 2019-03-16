#include <cstdio>

using namespace std;

const int NMAX = 3e5;

int m,n,k;

int v[NMAX + 5];
int ans[NMAX + 5];

int main(){
   
    scanf("%d %d %d\n",&m,&n,&k);

    if(m > n){
        printf("-1\n");
        return 0;
    }

    v[0] = 1;

    for(int i = 1;i <= m;i++){
        scanf("%d",&v[i]);
        if(v[i] == -1){
            v[i] = v[i - 1];
        }
        if(v[i] < v[i - 1]){
            printf("-1\n");
            return 0;
        }
    }

    int val = k;

    int id = 1;

    for(int i = 1;i <= n - m;i++){
        if(id > m || v[id] >= val){
            val--;
            id = 1;
        }
        if(val <= 0 || v[1] >= val || id > m){
            printf("-1\n");
            return 0;
        }
        ans[i] = val;
        id++;
    }

    for(int i = 1;i <= n;i++){
        if(ans[i] == 0){
            ans[i] = v[i - (n - m)];
        }
        printf("%d ",ans[i]);
    }

    return 0;
}
