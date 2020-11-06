#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;
int a[105][105];
int main() {


    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                scanf("%d",&a[i][j]);
            }
        }

        long long ans = 0;

        for(int i = 1;i <= (n + 1) / 2;i++){
            for(int j = 1;j <= (m + 1) / 2;j++){
                vector<int> v = {a[i][j]};
                if(n - i + 1 != i){
                    v.push_back(a[n - i + 1][j]);
                }
                if(m - j + 1 != j){
                    v.push_back(a[i][m - j + 1]);
                }
                if(n - i + 1 != i && m - j + 1 != j){
                    v.push_back(a[n - i + 1][m - j + 1]);
                }
                
                sort(v.begin(),v.end());
                for(int i = 0;i < (int)v.size() / 2;i++){
                    ans -= v[i]; 
                }
                reverse(v.begin(),v.end());
                for(int i = 0;i < (int)v.size() / 2;i++){
                    ans += v[i]; 
                }
            }
        }

        printf("%lld\n",ans);
    }

    return 0;
}
