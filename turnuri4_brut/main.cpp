#include <cstdio>

using namespace std;

FILE *f = fopen("turnuri4.in","r");
FILE *g = fopen("turnuri4.ok","w");

int n;
int v[int(1e5) + 5];

int S[int(1e5) + 5],len;
int st[int(1e5) + 5];
int dr[int(1e5) + 5];

long long solve(){
    S[len = 0] = 0;

    for(int i = 1;i <= n;i++){
        while(len && v[S[len]] <= v[i]){
            len--;
        }
        st[i] = S[len];
        S[++len] = i;
    }

    S[len = 0] = n + 1;

    for(int i = n;i;i--){
        while(len && v[S[len]] <= v[i]){
            len--;
        }
        dr[i] = S[len];
        S[++len] = i;
    }

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        ans += dr[i] - st[i] - 1;
    }

    return ans;
}

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1;i <= n;i++){
        int tmp = v[i];
        v[i] = 0;
        fprintf(g,"%lld\n",solve());
        v[i] = tmp;
    }

    return 0;
}
