#include <cstdio>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("ok","w");

int v[10000];

int main(){

    int n,k;

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int val;
        fscanf(f,"%d",&v[i]);
        for(int j = 1;j < i;j++){
            if(v[i] + v[j] == k){
                fprintf(g,"Yes\n");
                return 0;
            }
        }
    }

    fprintf(g,"No\n");

    fclose(f);
    fclose(g);

    return 0;
}
