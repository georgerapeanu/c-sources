#include <cstdio>

using namespace std;

FILE *f = fopen("pericol.in","r");
FILE *g = fopen("pericol.out","w");

const int NMAX = 2e5;
const int VMAX = 1e7;

int n;
int fr[VMAX + 1];
int v[NMAX + 1];
int mobius[VMAX + 5];
long long coef[VMAX + 1];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
        fr[v[i]]++;
    }

    mobius[1] = 0;

    for(int i = 2;i <= VMAX;i++){
        if(mobius[i] == 1){
            continue;
        }
        for(int j = 2 * i;j <= VMAX;j += i){
            mobius[j] = 1;
        }
    }

    mobius[1] = 1;
    for(int i = VMAX;i > 1;i--){
        if(mobius[i] == 0){
            mobius[i] = 1;
            for(int j = i;j <= VMAX;j += i){
                mobius[j] *= -1;
            }
            if(i <= VMAX / i){
                for(int j = i * i;j <= VMAX;j += i * i){
                    mobius[j] = 0;
                }
            }
        }
    }


    for(int i = 1;i <= VMAX;i++){
        int cnt = 0;
        for(int j = i;j <= VMAX;j += i){
            coef[j] += (j / i) * mobius[i];
            cnt += fr[j];
        }
        coef[i] *= cnt;
    }

    for(int i = VMAX;i;i--){
        for(int j = 2 * i;j <= VMAX;j += i){
            coef[j] += coef[i];
        }
    }


    for(int i = 1;i <= n;i++){
        fprintf(g,"%lld ",coef[v[i]] - v[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
