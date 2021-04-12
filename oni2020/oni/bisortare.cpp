#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int c,n,k;
int p[NMAX + 5];
int cst[NMAX + 5];
bool side[NMAX + 5];

int aib[NMAX + 5];

void update(int pos,int val){
    for(;pos <= n;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;

    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }

    return ans;
}

int main(){

    scanf("%d %d %d",&c,&n,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d",&p[i]);
    }

   
    long long ans = 0;

    for(int i = 1;i <= n;i++){
        side[i] = 1;
    }

    for(int i = 1;i <= n;i++){
        int tmp = query(p[i]);
        cst[i] = 2 * tmp  - p[i] + 1;
        ans += i - 1 - tmp;
        update(p[i],1);
    }

    sort(cst + 1,cst + 1 + n);


    for(int i = 1;i <= n;i++){
        if(cst[i] == 0){
            for(int j = i;j < n;j++){
                cst[j] = cst[j + 1];
            }
            break;
        }
    }

    for(int i = 1;i <= n;i++){
        if(c == 2 || k == i){
            printf("%lld ",ans);
        }
        ans += cst[i];
    }

    return 0;
}
