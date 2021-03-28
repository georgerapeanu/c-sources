#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n,m;
int a[NMAX + 5];
int b[NMAX + 5];
int u[NMAX + 5],l_u;
int v[NMAX + 5],l_v;
int cnt[NMAX + 5];

int solve(int n,int m,int a[],int b[]){
    
    int l = n;
    int r = m;

    cnt[n + 1] = 0;
    for(l = n;l >= 1;l--){
        cnt[l] = 0;
        while(r > 0 && b[r] > a[l]){
            r--;
        }
        if(r > 0 && a[l] == b[r]){
            cnt[l]++;
        }
        cnt[l] += cnt[l + 1];
    }

    l = 1;

    int ans = 0;

    for(r = 1;r <= m;r++){
        while(l <= n && a[l] <= b[r]){
            l++;
        }

        int x = 0;
        for(int jump = 1 << 20;jump;jump >>= 1){
            if(x + jump <= r && b[r] - b[x + jump] + 1 > l - 1){
                x += jump;
            }
        }

        ///b[r] - b[x] + 1 > (l - 1)

        ans = max(ans,cnt[l] + (r - x));
    }

    return ans;
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        }
        for(int i = 1;i <= m;i++){
            scanf("%d",&b[i]);
        }

        int ans = 0;
        l_u = l_v = 0;

        for(int i = 1; i <= n;i++){
            if(a[i] > 0){
                u[++l_u] = a[i];
            }
        }
        
        for(int i = 1; i <= m;i++){
            if(b[i] > 0){
                v[++l_v] = b[i];
            }
        }

        ans += solve(l_u,l_v,u,v);

        l_u = l_v = 0;

        for(int i = n; i;i--){
            if(a[i] < 0){
                u[++l_u] = -a[i];
            }
        }
        
        for(int i = m; i;i--){
            if(b[i] < 0){
                v[++l_v] = -b[i];
            }
        }

        ans += solve(l_u,l_v,u,v);
        
        printf("%d\n",ans);
    }

    return 0;
}
