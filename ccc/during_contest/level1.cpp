#include <bits/stdc++.h>

using namespace std;



int main(){

    int n;
    vector<int> price;

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        price.push_back(0);
        scanf("%d",&price.back());
    }

    pair<int,int> ans = {1e9,0};

    for(int i = 0;i < n;i++){
        ans = min(ans,make_pair(price[i],i));
    }

    printf("%d\n",ans.second);

    return 0;
}
