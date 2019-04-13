#include <cstdio>

using namespace std;

int n,m;
int a[105];
int b[105];

void build(int a[],int n) {
    if(n % 2 == 0) {
        if(n == 2) {
            a[1] = 3;
            a[2] = 4;
            return ;
        }
        for(int i = 1; i < n; i++) {
            a[i] = 1;
        }
        a[n] = (n - 2) / 2;
    }
    else {
        if(n == 1) {
            a[1] = 1;
            return ;
        }
        a[1] = 2;
        for(int i = 2; i < n; i++) {
            a[i] = 1;
        }
        a[n] = (n + 1) / 2;
    }
}

int main() {

    scanf("%d %d",&n,&m);

    build(a,n);
    build(b,m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            printf("%d ",a[i] * b[j]);
        }
        printf("\n");
    }

    return 0;
}
