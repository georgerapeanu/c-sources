#include <cstdio>

using namespace std;

const int NMAX = 1e5;

int t;
int n,m,q;
int v[NMAX + 5];
bool weight[NMAX + 5];

int main(){

    scanf("%d",&t);

    for(int test = 1;test <= t;test++){
        
        scanf("%d %d %d",&n,&m,&q);
        
        for(int i = 1;i <= n;i++){
            v[i] = 0;
            weight[i] = 1;
        }

        for(int i = 1;i <= m;i++){
            int p;
            scanf("%d",&p);
            weight[p] = 0;
        }

        for(int i = 1;i <= q;i++){
            int r;
            scanf("%d",&r);
            v[r]++;
        }

        for(int i = n;i;i--){
            for(int j = i + i;j <= n;j += i){
                v[j] += v[i];
            }
        }

        long long ans = 0;

        for(int i = 1;i <= n;i++){
            ans += v[i] * weight[i];
        }

        printf("Case #%d: %lld\n",test,ans);
    }

    return 0;
}
