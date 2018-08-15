#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int VMAX = 2e5;
const int NMAX = 2e5;

vector< int > Edges_with_val[VMAX + 5];
long long paths_with_multiple[VMAX + 5];
long long paths_with_gcd[VMAX + 5];
int nodes_with_val[VMAX + 5];

int DSU_father[NMAX + 5];
int DSU_size[NMAX + 5];

int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}

void init(){
    for(int i = 0;i < NMAX + 5;i++){
        DSU_father[i] = 0;
        DSU_size[i] = 1;
    }
}

int fi(int x){
    if(!DSU_father[x]){
        return x;
    }
    return DSU_father[x] = fi(DSU_father[x]);
}

long long u(int x,int y){
    x = fi(x);
    y = fi(y);
    if(x == y){
        return 0;
    }

    long long ans = 1LL * DSU_size[x] * DSU_size[y];

    if(DSU_size[x] < DSU_size[y]){
        DSU_size[y] += DSU_size[x];
        DSU_father[x] = y;
    }
    else{
        DSU_size[x] += DSU_size[y];
        DSU_father[y] = x;
    }

    return ans;
}

int N;
int V[NMAX + 5];
int X[NMAX + 5];
int Y[NMAX + 5];

int main(){

    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        scanf("%d",&V[i]);
        nodes_with_val[V[i]]++;
    }

    for(int i = 1;i < N;i++){
        scanf("%d %d",&X[i],&Y[i]);
        Edges_with_val[gcd(V[X[i]],V[Y[i]])].push_back(i);
    }

    init();

    for(int i = 1;i <= VMAX;i++){
        for(int j = i;j <= VMAX;j += i){
            for(auto it:Edges_with_val[j]){
                paths_with_multiple[i] += u(X[it],Y[it]);
            }
        }
        for(int j = i;j <= VMAX;j += i){
             for(auto it:Edges_with_val[j]){
                DSU_father[X[it]] = 0;
                DSU_father[Y[it]] = 0;
                DSU_size[X[it]] = 1;
                DSU_size[Y[it]] = 1;
            }
        }
    }

    for(int i = VMAX;i;i--){
        paths_with_gcd[i] = paths_with_multiple[i];
        for(int j = 2 * i;j <= VMAX;j += i){
            paths_with_gcd[i] -= paths_with_gcd[j];
        }
    }

    for(int i = 1;i <= VMAX;i++){
        paths_with_gcd[i] +=  nodes_with_val[i];
        if(paths_with_gcd[i]){
            printf("%d %I64d\n",i,paths_with_gcd[i]);
        }
    }

    return 0;
}
