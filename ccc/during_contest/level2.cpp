#include <bits/stdc++.h>

using namespace std;

int main(){

    int n,m;
    vector<int> price;
    vector<int> pref_sum;

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        price.push_back(0);
        scanf("%d",&price.back());
        pref_sum.push_back(price.back());
        if(i > 1){
            pref_sum[i - 1] += pref_sum[i - 2];
        }
    }

    scanf("%d",&m);

    printf("%d\n",m);

    for(int k = 1;k <= m;k++){
        int id,t;
        scanf("%d %d",&id,&t);
        pair<int,int> ans = {1e9,0};
        for(int i = 0;i + t <= n;i++){
            ans = min(ans,make_pair(pref_sum[i + t - 1] - (i > 0 ? pref_sum[i - 1]:0),i));
        }
        printf("%d %d\n",id,ans.second);
    }

    return 0;
}
