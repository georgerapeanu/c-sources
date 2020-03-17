#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("arbciclu.in","r");
FILE *g = fopen("arbciclu.out","w");

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];

int t;
int n,m;

int main(){
    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d %d",&n,&m);
        for(int i = 1;i <= m;i++){

        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
