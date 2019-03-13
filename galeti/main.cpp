#include <cstdio>

using namespace std;

FILE *f = fopen("galeti2.in","r");
FILE *g = fopen("galeti2.out","w");

int n;
long long e;

int main(){
    fscanf(f,"%d %lld",&n,&e);

    for(int i = 2;i <= n;i++){
        if(e - 1LL * (i - 1) * (i - 2) / 2 - (n - i) <= i - 1){

            int tmp = e - 1LL * (i - 1) * (i - 2) / 2 - (n - i);


            for(int j = i - 1;j > tmp;j--){
                fprintf(g,"%d %d\n",j,j - 1);
            }

            fprintf(g,"%d %d\n",i,tmp);

            for(int j = tmp;j > 1;j--){
                fprintf(g,"%d %d\n",j,j - 1);
            }

            for(int j = i + 1;j <= n;j++){
                fprintf(g,"%d %d\n",j,1);
            }
            break;
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
