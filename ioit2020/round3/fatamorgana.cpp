#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 3e5;

int n;
unsigned int v[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%u",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    for(int i = 1;i <= n / 2;i++){
        if(v[i] == v[i + n / 2]){
            for(int j = 1;j <= n;j++){
                printf("%d ",v[j]);
            }
            return 0;
        }
    }

    int sgn = 1;

    for(int i = 1;i < n / 2;i++){
        printf("%d %d ",v[i],v[i + n / 2]);
        sgn *= -1;
    }

    if(sgn == -1){
        printf("%d %d ",v[n / 2],v[n]);
    }else{
        printf("%d %d ",v[n],v[n / 2]);
    }

    return 0;
}
