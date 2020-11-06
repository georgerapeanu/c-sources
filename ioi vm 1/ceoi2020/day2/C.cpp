#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int r,c,q;

struct matrix_t{
    int n,m;
    int a[105][105];

    matrix_t(int n,int m){
        this->n = n;
        this->m = m;
        for(int i = 0;i <= n;i++){
            for(int j = 0;j <= m;j++){
                this->a[i][j] = 0;
            }
        }

    }

    matrix_t operator *(const matrix_t &other)const{
        matrix_t ans(n,other.m);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= other.m;j++){
                for(int k = 1;k <= m;k++){
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return ans;
    }
};

int main(){

    scanf("%d %d %d\n",&r,&c,&q);
    matrix_t dp_trans(c,c);
    matrix_t base(c,1);

    vector<matrix_t> powers;

    for(int i = 1;i <= c;i++){
        dp_trans.a[i][i] = 1;
        if(i > 1)dp_trans.a[i][i - 1] = 1;
        if(i < c)dp_trans.a[i][i + 1] = 1;
    }

    powers.push_back(dp_trans);

    for(int i = 1;i <= 30;i++){
        powers.push_back(powers[i - 1] * powers[i - 1]);
    }

    while(q--){
        char piece;
        int x,y;
        scanf("%c %d %d\n",&piece,&x,&y);

        if(piece == 'P'){
            if(x != y){
                printf("0 0\n");
            }
            else{
                printf("1 %d\n",r - 1);
            }
        }
        else if(piece == 'R'){
            if(x != y){
                printf("2 2\n");
            }
            else{
                printf("1 1\n");
            }
        }
        else if(piece == 'Q'){
            if(1 + x == r + y || 1 - x == r - y || x == y || 1 == r){
                printf("1 1\n");
            }
            else{

                int cnt = 0;
                int a,b;
                ///two rock moves
                cnt += 2;
                ///rock move bishop move
                a = 1;
                b = r + y - a;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }
                
                a = 1;
                b = a + y - r;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }
                
                b = x;
                a = r + y - b;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }

                b = x;
                a = r - y + b;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }
                ///bishop move rock move
                
                a = r;
                b = 1 + x - a;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }

                a = r;
                b = a + x - 1;
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }

                b = y;
                a = 1 + x - b;
                
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }

                b = y;
                a = 1 - x + b;
                
                if(1 <= a && a <= r && 1 <= b && b <= c){
                    cnt++;
                }

                ///bishop move bishop move
                if((1 + x + r - y) % 2 == 0){
                    a = (1 + x + r - y) / 2;
                    b = (1 + x - a);
                    if(1 <= a && a <= r && 1 <= b && b <= c){
                        cnt++;
                    }
                }

                if((1 - x + r + y) % 2 == 0){
                    a = (1 - x + r + y) / 2;
                    b = (a - 1 + x);
                    if(1 <= a && a <= r && 1 <= b && b <= c){
                        cnt++;
                    }
                }
                printf("2 %d\n",cnt);
            }
        }
        else if(piece == 'K'){
            base.a[x][1] = 1;
            matrix_t ans(c,c);
            bool fst = true;
            int e = r - 1;
            for(int h = 30;h >= 0;h--){
                if((e >> h)){
                    e ^= (1 << h);
                    if(fst){
                        ans = powers[h];
                        fst = false;
                    }
                    else{
                        ans = ans * powers[h];
                    }
                }
            }
            int cnt = (ans * base).a[y][1];
            base.a[x][1] = 0;
            printf("%d %d\n",r - 1,cnt);
        }
        else{
            printf("0 0\n");
        }
    }

    return 0;
}
