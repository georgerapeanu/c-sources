#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;

    scanf("%d",&t);

    while(t--){
        int n,d;
        bool hasBigger = false;
        pair<int,int> mi = {1e9,1e9};

        scanf("%d %d",&n,&d);

        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            if(val > d){
                hasBigger = true;
            }
            if(val < mi.first){
                mi.second = mi.first;
                mi.first = val;
            }else if(val < mi.second){
                mi.second = val;
            }
        }

        if(hasBigger == true && mi.first + mi.second > d){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
    }

    return 0;
}
