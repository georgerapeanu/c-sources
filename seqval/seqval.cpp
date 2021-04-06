#include <cstdio>

using namespace std;

const int NMAX = 500000;
const int MOD = 1e9 + 7;

int n;
int st[NMAX + 5],len;
int v[NMAX + 5];

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}


int sum_maximum(){
    int ans = 0;
    v[0] = v[n + 1] = 1e9;

    len = 0;
    for(int i = 1;i <= n + 1;i++){
        while(len > 0 && v[st[len]] <= v[i]){
            ans = add(ans,mult(mult(st[len] - st[len - 1],i - st[len]),st[len]));
            len--;
        }
        st[++len] = i;
    }

    return ans;
}

int main(){
    freopen("seqval.in","r",stdin);
    freopen("seqval.out","w",stdout);

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    int ans = sum_maximum();

    for(int i = 1;i <= n;i++){
        v[i] *= -1;
    }

    ans = scad(ans,sum_maximum());

    printf("%d\n",ans);
    

    return 0;
}
