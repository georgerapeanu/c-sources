#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("puzzle3.in","r");
FILE *g = fopen("puzzle3.out","w");

const int NMAX = 1e5;

char _to_val[300];

struct state_t{
    bool need_t;
    int x;
    int y;
    int z;
    bool prod_t;

    state_t(){
        need_t = 0;
        x = 0;
        y = 0;
        z = 0;
        prod_t = 0;
    }

    state_t(bool t,char a,char b,char c){
        need_t = t;
        x = _to_val[(int)a];
        y = _to_val[(int)b];
        z = _to_val[(int)c];
        prod_t = (x + y + (int)t >= 10);
    }
    
    state_t(bool t,int a,int b,int c,bool nt){
        need_t = t;
        x = a;
        y = b;
        z = c;
        prod_t = nt;
    }

    bool is_valid(){
        if((x + y + (int)need_t) % 10 != z){
            return false;
        }
        if((x + y + (int)need_t) / 10 != (int)prod_t){
            return false;
        }
        return true;
    }

    bool operator < (const state_t &other)const{
        if(need_t != other.need_t) return need_t < other.need_t;
        if(x * 121 + y * 11 + z != other.x * 121 + other.y * 11 + other.z) return x * 121 + y * 11 + z < other.x * 121 + other.y * 11 + other.z;
        return prod_t < other.prod_t;
    }

    int to_val(){
        return need_t * 2662 + x * 242 + y * 22 + z * 2 + prod_t;
    }
};

state_t smen[2 * 2662 + 11 * 242 + 11 * 22 + 11 * 2 + 2 + 5];
bool viz[2 * 2662 + 11 * 242 + 11 * 22 + 11 * 2 + 2 + 5];

int t,n;
int dp[NMAX + 5][2];
char a[NMAX + 5];
char b[NMAX + 5];
char c[NMAX + 5];

void add0(char a[],int len_a,int n){
    for(int i = n;i > n - len_a;i--){
        a[i] = a[i - (n - len_a)];
    }
    for(int i = n - len_a;i;i--){
        a[i] = '0';
    }
}

void up(state_t a,state_t b){
    state_t tmp = smen[a.to_val()];
    viz[a.to_val()] = true;
    if((tmp.x == 0) + (tmp.y == 0) + (tmp.z == 0) > (b.x == 0) + (b.y == 0) + (b.z == 0)){
        smen[a.to_val()] = b;
    }
}

int main(){

    for(int i = 0;i <= 9;i++){
        _to_val[i + '0'] = i;
    }

    _to_val['*'] = 10;

    state_t(0,'0','5','5').is_valid();

    for(int t = 0;t < 2;t++){
        for(char a = '0';a <= '9';a++){
            for(char b = '0';b <= '9';b++){
                for(char c = '0';c <= '9';c++){
                    state_t tmp(t,a,b,c);
                    if(tmp.is_valid()){
                        up(state_t(tmp.need_t,tmp.x,tmp.y,tmp.z,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,tmp.x,tmp.y,   10,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,tmp.x,   10,tmp.z,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,tmp.x,   10,   10,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,   10,tmp.y,tmp.z,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,   10,tmp.y,   10,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,   10,   10,tmp.z,tmp.prod_t),tmp);
                        up(state_t(tmp.need_t,   10,   10,   10,tmp.prod_t),tmp);
                    }
                }
            }
        }
    }

    fscanf(f,"%d\n",&t);

    while(t--){
        fgets(a + 1,NMAX + 5,f);
        fgets(b + 1,NMAX + 5,f);
        fgets(c + 1,NMAX + 5,f);
        
        int len_a = strlen(a + 1);len_a -= (a[len_a] == '\n');
        int len_b = strlen(b + 1);len_b -= (b[len_b] == '\n');
        int len_c = strlen(c + 1);len_c -= (c[len_c] == '\n');
        
        int n = max(max(len_a,len_b),len_c);
        
        add0(a,len_a,n);
        add0(b,len_b,n);
        add0(c,len_c,n);

        dp[n + 1][1] = -1;
        dp[n + 1][0] = 0;

        for(int i = n;i >= 1;i--){
            dp[i][0] = dp[i][1] = -1;
            if(dp[i + 1][0] != -1){
                if(viz[state_t(0,_to_val[(int)a[i]],_to_val[(int)b[i]],_to_val[(int)c[i]],0).to_val()]){
                    dp[i][0] = 0;
                }
                if(viz[state_t(0,_to_val[(int)a[i]],_to_val[(int)b[i]],_to_val[(int)c[i]],1).to_val()]){
                    dp[i][1] = 0;
                }
            }
            if(dp[i + 1][1] != -1){
                if(viz[state_t(1,_to_val[(int)a[i]],_to_val[(int)b[i]],_to_val[(int)c[i]],0).to_val()]){
                    dp[i][0] = 1;
                }
                if(viz[state_t(1,_to_val[(int)a[i]],_to_val[(int)b[i]],_to_val[(int)c[i]],1).to_val()]){
                    dp[i][1] = 1;
                }
            }
        }

        int wut = (dp[1][0] != -1 ? 0:1);

        for(int i = 1;i <= n;i++){
            state_t tmp = smen[state_t(dp[i][wut],_to_val[(int)a[i]],_to_val[(int)b[i]],_to_val[(int)c[i]],wut).to_val()];
            a[i] = tmp.x + '0';
            b[i] = tmp.y + '0';
            c[i] = tmp.z + '0';
            wut = dp[i][wut];
        }
        a[n + 1] = '\n';a[n + 2] = '\0';
        b[n + 1] = '\n';b[n + 2] = '\0';
        c[n + 1] = '\n';c[n + 2] = '\0';
        for(int i = 1;i <= 2 + len_a;i++)a[i] = a[i + (n - len_a)];
        for(int i = 1;i <= 2 + len_b;i++)b[i] = b[i + (n - len_b)];
        for(int i = 1;i <= 2 + len_c;i++)c[i] = c[i + (n - len_c)];
        fprintf(g,"%s%s%s",a + 1,b + 1,c + 1);
    }

    fclose(f);
    fclose(g);

    return 0;
}
