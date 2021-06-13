#include <bits/stdc++.h>

using namespace std;

int tests;
int n,k;

int main(){

    cin >> tests;

    for(int test = 1;test <= tests;test++){
        printf("Case #%d: ",test);

        scanf("%d %d",&n,&k);

        vector<int> p;
        for(int i = 1;i <= n;i++){
            int x;
            scanf("%d",&x);
            p.push_back(x);
        }

        sort(p.begin(),p.end());
        p.resize(unique(p.begin(),p.end()) - p.begin());

        vector<int> sz;
        int last = 0;
        for(auto it:p){
            sz.push_back(it - last - 1);
            last = it;
        }
        sz.push_back(k - last);

        int ans = 0;

        for(auto it:sz){
            ans = max(ans,it);
        }

        pair<int,int> bst = {-1,-1};

        for(int i = 0;i < (int)sz.size();i++){
            int cst;
            if(i == 0 || i == (int)sz.size() - 1){
                cst = sz[i];
            }else{
                cst = (sz[i] + 1) / 2;
            }
            if(cst > bst.first){
                bst.second = bst.first;
                bst.first = cst;
            }else if(cst > bst.second){
                bst.second = cst;
            }
        }
        ans = max(ans,bst.first + bst.second);

        printf("%.8f\n",((double)ans) / k);
    }

    return 0;
}
