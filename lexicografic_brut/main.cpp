#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f =fopen("lexicografic.in","r");
FILE *g =fopen("lexicografic.ok","w");

int t;
int n,k;
int v[250005];

int main(){

    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d %d",&n,&k);

        for(int i = 1;i <= n;i++){
            fscanf(f,"%d",&v[i]);
        }

        for(int i = 1;i <= n;i++){
            pair<int,int> bst = {v[i],i};
            for(int j = i + 1;j <= min(n,i + k);j++){
                bst = min(bst,{v[j],j});
            }
            k -= (bst.second - i);
            for(int j = bst.second;j > i;j--){
                swap(v[j],v[j - 1]);
            }
        }

        for(int i = 1;i <= n;i++){
            fprintf(g,"%d ",v[i]);
        }
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
