#include <bits/stdc++.h>

using namespace std;

int a[505][505];

int lst = 0;

void add_val(int x,int y) {
    if(a[x][y] == 0) {
        a[x][y] = ++lst;
    }
}


int main() {
    int n;
    scanf("%d",&n);

    if(n < 3) {
        printf("-1\n");
        return 0;
    }

    for(int i = 1; i <= n - 3; i++) {
        if(i % 2 == 1) {
            for(int j = n; j >= i; j--) {
                add_val(j,i);
            }
            for(int j = i; j <= n; j++) {
                add_val(i,j);
            }
        }
        else {
            for(int j = n; j >= i; j--) {
                add_val(i,j);
            }
            for(int j = i; j <= n; j++) {
                add_val(j,i);
            }
        }
    }

    if(n % 2 == 0) {
        add_val((n - 3) + 2,(n - 3) + 3);
        add_val((n - 3) + 2,(n - 3) + 2);
        add_val((n - 3) + 3,(n - 3) + 2);
        add_val((n - 3) + 3,(n - 3) + 1);
        add_val((n - 3) + 3,(n - 3) + 3);
        add_val((n - 3) + 1,(n - 3) + 2);
        add_val((n - 3) + 1,(n - 3) + 1);
        add_val((n - 3) + 1,(n - 3) + 3);
        add_val((n - 3) + 2,(n - 3) + 1);
    }
    else {
        add_val((n - 3) + 3,(n - 3) + 2);
        add_val((n - 3) + 2,(n - 3) + 2);
        add_val((n - 3) + 2,(n - 3) + 3);
        add_val((n - 3) + 1,(n - 3) + 3);
        add_val((n - 3) + 3,(n - 3) + 3);
        add_val((n - 3) + 2,(n - 3) + 1);
        add_val((n - 3) + 1,(n - 3) + 1);
        add_val((n - 3) + 3,(n - 3) + 1);
        add_val((n - 3) + 1,(n - 3) + 2);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
