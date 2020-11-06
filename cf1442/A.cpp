#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[30005];
int v[30005];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
        }

        int scad = 0;

        for(int i = 1;i <= n;i++){
            if(i > 1){
                scad += max(0,v[i] - v[i - 1]);
            }
            a[i] = v[i] - scad;
        }

        bool ok = true;

        for(int i = n;i;i--){
            if(a[i] < 0){
                ok = false;
            }
        }

        printf(ok ? "YES\n":"NO\n");
    }

    return 0;
}
