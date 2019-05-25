#include <cstdio>

using namespace std;

const int NMAX = 1e5;

int n,m;
int v[NMAX + 5];

int main(){
    scanf("%d %d\n",&n,&m);

    for(int i = 1;i <= m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        v[l]++;
        v[r + 1]--;
    }

    int total = 0;

    for(int i = 1;i <= n;i++){
        v[i] += v[i - 1];
        total += (v[i] == m);
    }

    printf("%d\n",total);

    return 0;
}
