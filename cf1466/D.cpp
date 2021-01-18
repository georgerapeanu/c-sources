#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int t;
int n;
int gr[NMAX + 5];
int v[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
            gr[i] = -1;
        }


        for(int i = 1;i < n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            gr[u]++;
            gr[v]++;
        }

        vector<pair<int,int> > tmp;

        long long ans = 0;

        for(int i = 1;i <= n;i++){
            ans += v[i];
            if(gr[i] > 0){
                tmp.push_back({v[i],gr[i]});
            }
        }

        sort(tmp.begin(),tmp.end());


        for(int k = 1;k < n;k++){
            printf("%lld ",ans);
            while(tmp.empty() == false && tmp.back().second == 0){
                tmp.pop_back();
            }
            if(tmp.empty() == false){
                ans += tmp.back().first;
                tmp.back().second--;
            }
        }
        printf("\n");
    }


    return 0;
}
