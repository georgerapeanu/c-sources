#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

FILE *g = fopen("tablou.in","w");

const int NMAX = 1000;
const int MMAX = 1000;
const int KMAX = 1e4;
const int OPMAX = 1e8;///K^2<= OP,NMK <= OP

int main(){
    srand(time(NULL));
    int n = rand() % NMAX + 1;
    int m = rand() % MMAX + 1;
    int k = rand() % min(KMAX,min((int)sqrt(OPMAX),OPMAX / n / m)) + 1;

    fprintf(g,"%d %d\n",n,m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            fprintf(g,"%d",rand() % 10);
        }
        fprintf(g,"\n");
    }

    fprintf(g,"%d\n",k);

    for(int i = 1;i <= k;i++){
        int x = rand() % n + 1;
        int xx = rand() % n + 1;
        int y = rand() % m + 1;
        int yy = rand() % m + 1;
        int c = rand() % 10;

        if(xx < x){
            swap(x,xx);
        }
        if(yy < y){
            swap(y,yy);
        }

        fprintf(g,"%d %d %d %d %d\n",x,y,xx,yy,c);
    }

    fclose(g);

    return 0;
}
