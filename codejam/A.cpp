#include <bits/stdc++.h>

using namespace std;

int n,t;
int v[105][105];

int fr[105];

int main() {

    scanf("%d",&t);

    for(int x = 1; x <= t; x++) {
        int r = 0,c = 0,tr = 0;

        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d",&v[i][j]);
            }
        }

        for(int i = 1; i <= n; i++) {
            tr += v[i][i];
        }

        for(int i = 1; i <= n; i++) {
            memset(fr,0,sizeof(fr));
            for(int j = 1; j <= n; j++) {
                if(fr[v[i][j]]) {
                    r++;
                    break;
                }
                fr[v[i][j]]++;
            }
            memset(fr,0,sizeof(fr));
            for(int j = 1; j <= n; j++) {
                if(fr[v[j][i]]) {
                    c++;
                    break;
                }
                fr[v[j][i]]++;
            }
        }

        printf("Case #%d: %d %d %d\n",x,tr,r,c);
    }

    return 0;
}
