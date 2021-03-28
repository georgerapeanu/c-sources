#include <cstdio>

using namespace std;

const int NMAX = 5e5;

int n;
int v[NMAX + 5];
int fail[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    fail[1] = 0;

    for(int i = 2;i <= n;i++){
        int k = fail[i - 1];

        while(k > 0 && v[k + 1] != v[i]){
            k = fail[k];
        }
        if(v[k + 1] == v[i]){
            k++;
        }
        fail[i] = k;
    }

    printf("%d\n",n - fail[n]);

    return 0;
}
