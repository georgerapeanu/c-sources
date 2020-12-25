#include <bits/stdc++.h>

using namespace std;

int t;
int n;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        unordered_map<int,int> tmp;

        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            tmp[val]++;
        }

        bool ok = false;

        for(auto it:tmp){
            ok |= (it.second > 1);
        }

        printf(ok ? "YES\n":"NO\n");
    }

    return 0;
}
