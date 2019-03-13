#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

FILE *g1 = fopen("eq4.in","w");
FILE *g2 = fopen("eq4.ok","w");

const int W1 = 20;
const int W2 = 80;
const int NMAX = 1e5;
const int vmax = 1e4;
const int q_min = -100;
const int q_max = 100;
const long long QMAX = 1e8;

char tmp[NMAX + 5];
int len[vmax + 5];

int coef[10];

int main(){

    len[0] = 0;
    for(int i = 1;i < vmax;i++){
        len[i] = 1 + len[i / 10];
    }
    len[0] = 1;

    srand(time(NULL));
    int VMAX = rand() % vmax + 1;
    int t = (rand() % (W1 + W2) < W1 ? 1:2);

    fprintf(g1,"%d\n",t);

    int n = rand() % NMAX + 1;
    int sz = 0;

    while(sz <= n){
        char sgn = (rand() % 2 == 0 ? '-':'+');
        int val = rand() % VMAX;
        int wut = rand() % 5;

        int b_val = val;
        if((wut != 0) + 1 + len[val] + sz > n){
            break;
        }

        tmp[++sz] = sgn;

        if(wut == 0){
            for(int i = sz + len[val];i > sz;i--){
                tmp[i] = val % 10 + '0';
                val /= 10;
            }
            sz += len[b_val];
        }
        else{
            if(val == 1){
                if(rand() & 1){
                    tmp[++sz] = '1';
                }
            }
            else{
                for(int i = sz + len[val];i > sz;i--){
                    tmp[i] = val % 10 + '0';
                    val /= 10;
                }
                sz += len[b_val];
            }

            tmp[++sz] = (wut == 4 ? 't':('x' + wut - 1));
        }
        coef[wut] += (sgn == '-' ? -1:1)* b_val;
    }

    n = sz;

//    fprintf(g1,"%d\n",n);
    tmp[n + 1] = '\0';
    fputs(tmp + 1,g1);
    int st = rand() % (q_max - q_min + 1) + q_min;
    int dr = rand() % (q_max - q_min + 1) + q_min;
    if(dr < st){
        swap(st,dr);
    }

    long long qMAX = rand() % QMAX;
    long long qmax = rand() % qMAX;
    long long qval = rand() % (2 * qmax + 1) - qmax;

    fprintf(g1,"\n%d %d %lld\n",st,dr,qval);

    if(t == 1){
        long long ans = 0;
        for(int i = 0;i < 5;i++){
            ans += coef[i];
        }
        fprintf(g2,"%lld\n",ans);
    }
    else{

        long long ans = 0;

        for(int x = st;x <= dr;x++){
            for(int y = st;y <= dr;y++){
                for(int z = st;z <= dr;z++){
                    for(int t = st;t <= dr;t++){
                        long long val = coef[0] + 1LL * coef[1] * x + 1LL * coef[2] * y + 1LL * coef[3] * z + 1LL * coef[4] * t;
                        ans += (val == qval);
                    }
                }
            }
        }

        fprintf(g2,"%lld",ans);
    }

    fclose(g1);
    fclose(g2);

    return 0;
}
