#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

int n;
int v[100000];

int main(){
    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
        if(v[i] <= 0 || v[i] > n){
            v[i] = 0;
        }
    }

    for(int i = 1;i <= n;i++){
        while(v[i] && v[i] != i){
            if(v[v[i]] == v[i]){
                v[i] = 0;
                break;
            }
            swap(v[i],v[v[i]]);
        }
    }

    for(int i = 1;i <= n;i++){
        if(v[i] == 0){
            fprintf(g,"%d ",i);
            return 0;
        }
    }

    fprintf(g,"%d ",n + 1);

    fclose(f);
    fclose(g);

    return 0;
}
