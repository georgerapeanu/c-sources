#include <bits/stdc++.h>

using namespace std;

int t;
int n;
vector<int> tmp;
vector<int> active;
vector<long long> strengths[200005];
int u[200005];
int s[200005];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        active.clear();
        for(int i = 1;i <= n;i++){
            scanf("%d",&u[i]);
            strengths[i].clear();
        }
        
        for(int i = 1;i <= n;i++){
            scanf("%d",&s[i]);
            strengths[u[i]].push_back(s[i]);
        }

        for(int i = 1;i <= n;i++){
            sort(strengths[i].begin(),strengths[i].end());
            reverse(strengths[i].begin(),strengths[i].end());
            for(int j = 1;j < (int)strengths[i].size();j++){
                strengths[i][j] += strengths[i][j - 1];
            }
            if(strengths[i].empty() == false){
                active.push_back(i);
            }
        }

        for(int k = 1;k <= n;k++){
            tmp.clear();
            long long ans = 0;
            for(auto it:active){
                if((int)strengths[it].size() < k){
                    continue;
                }
                tmp.push_back(it);
                ans += strengths[it][int(strengths[it].size() / k) * k - 1];
            }
            active = tmp;
            printf("%lld ",ans);
        }
        printf("\n");
    }

    return 0;
}
