#include <cstdio>
#include <unordered_map>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

unordered_map<int,int> m;

int main(){

    int n,k;

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int val;
        fscanf(f,"%d",&val);
        if(m[k - val] == 1){
            fprintf(g,"Yes\n");
            return 0;
        }
        m[val] = 1;
    }

    fprintf(g,"No\n");

    fclose(f);
    fclose(g);

    return 0;
}
