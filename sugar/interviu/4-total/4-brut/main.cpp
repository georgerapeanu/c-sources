#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("ok","w");

int n;
int v[100000];

int main(){
    fscanf(f,"%d",&n);
    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    int mex = 1;
    for(int i = 1;i <= n;i++){
        mex += (v[i] == mex);
    }

    fprintf(g,"%d",mex);

    return 0;
}
