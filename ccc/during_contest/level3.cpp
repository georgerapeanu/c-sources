#include <bits/stdc++.h>

using namespace std;

int main(){

    int n,m;
    vector<int> price;

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        price.push_back(0);
        scanf("%d",&price.back());
    }

    scanf("%d",&m);

    printf("%d\n",m);

    for(int k = 1;k <= m;k++){
        int id,p,l,r;
        scanf("%d %d %d %d",&id,&p,&l,&r);
        pair<int,int> ans = {1e9,0};
        for(int i = l;i <= r;i++){
            ans = min(ans,make_pair(price[i],i));
        }
        printf("%d %d %d\n",id,ans.second,p);
    }

    return 0;
}
