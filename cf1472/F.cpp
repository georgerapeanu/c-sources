#include <bits/stdc++.h>

using namespace std;

struct matrix_t{
    int n,m;
    int a[5][5];

    matrix_t(){
        ;
    }
    

    matrix_t(int n,int m){
        this->n = n;
        this->m = m;
    }

    matrix_t operator * (const matrix_t &other)const{
        matrix_t ans(this->n,other.m);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                ans.a[i][j] = 0;
                for(int k = 0;k < this->m;k++){
                    ans.a[i][j] |= (this->a[i][k] & other.a[k][j]);
                }
            }
        }
        return ans;
    }
};

int t;
int n,m;

matrix_t lgpow(matrix_t base,int e){
    matrix_t ans = base;

    for(int i = 0;i < ans.n;i++){
        for(int j = 0;j < ans.m;j++){
            ans.a[i][j] = (i == j);
        }
    }

    while(e){
        if(e & 1){
            ans = ans * base;
        }
        base = base * base;
        e >>= 1;
    }

    return ans;
}

int main(){

    matrix_t base(4,4);
    base.a[0][0] = 0;
    base.a[0][1] = 0;
    base.a[0][2] = 0;
    base.a[0][3] = 1;
    base.a[1][0] = 0;
    base.a[1][1] = 0;
    base.a[1][2] = 1;
    base.a[1][3] = 0;
    base.a[2][0] = 0;
    base.a[2][1] = 1;
    base.a[2][2] = 0;
    base.a[2][3] = 0;
    base.a[3][0] = 1;
    base.a[3][1] = 0;
    base.a[3][2] = 0;
    base.a[3][3] = 1;

    matrix_t init(4,1);

    init.a[0][0] = 0;
    init.a[1][0] = 0;
    init.a[2][0] = 0;
    init.a[3][0] = 1;

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        map<int,int> confs;

        for(int i = 1;i <= m;i++){
            int r,c;
            scanf("%d %d",&r,&c);
            confs[c] |= (1 << (r - 1));
        }
        matrix_t dp = init;
        int lst = 0;

        for(auto it:confs){
            dp = lgpow(base,it.first - lst) * dp;
            lst = it.first;
            for(int conf = 0;conf < 4;conf++){
                if(conf & it.second){
                    dp.a[conf][0] = 0;
                }
            }
            for(int conf = 0;conf < 4;conf++){
                if(!(conf & it.second)){
                    dp.a[conf | it.second][0] |= dp.a[conf][0];
                    dp.a[conf][0] = 0;
                }
            }
        }
        dp = lgpow(base,n - lst) * dp;
        printf(dp.a[3][0] == 1 ? "YES\n":"NO\n");
    }

    return 0;
}
