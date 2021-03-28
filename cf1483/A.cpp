#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n,m;

int fr[NMAX + 5];
vector<int> available[NMAX + 5];
int taken[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);
        for(int i = 1;i <= n;i++){
            available[i].clear();
            fr[i] = 0;
        }
        for(int i = 1;i <= m;i++){
            taken[i] = 0;
        }

        for(int i = 1;i <= m;i++){
            int k;
            scanf("%d",&k);
            for(int j = 1;j <= k;j++){
                int frien;
                scanf("%d",&frien);
                available[frien].push_back(i);
            }
        }

        for(int i = 1;i <= n;i++){
            for(auto it:available[i]){
                if(taken[it] == 0){
                    taken[it] = i;
                    fr[i]++;
                }
            }
            for(auto it:available[i]){
                if(taken[it] != i && fr[i] < (m + 1) / 2){
                    fr[taken[it]]--;
                    taken[it] = i;
                    fr[taken[it]]++;
                }
            }
        }

        bool ok = true;

        for(int i = 1;i <= n;i++){
            ok &= (fr[i] <= (m + 1) / 2);
        }
        for(int i = 1;i <= m;i++){
            ok &= (taken[i] != 0);
        }

        printf(ok ? "YES\n":"NO\n");

        if(ok){
            for(int i = 1;i <= m;i++){
                printf("%d ",taken[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
