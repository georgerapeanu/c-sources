#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;
vector<int> red;
vector<int> blue;

int main(){

    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);

        red = vector<int>(n);
        blue = vector<int>(m);

        for(auto &it:red){
            scanf("%d",&it);
        }
    
        for(auto &it:blue){
            scanf("%d",&it);
        }
    
        blue.push_back(0);
        blue.push_back(1e9 + 2);
    

        sort(red.begin(),red.end());
        sort(blue.begin(),blue.end());
    
        int ans = 0;
    
        for(int i = 0;i < (int)blue.size() - 1;i++){
            int local_ans = lower_bound(red.begin(),red.end(),blue[i + 1]) - lower_bound(red.begin(),red.end(),blue[i] + 1);
            if(local_ans > ans){
                ans = local_ans;
            }
        }
    
        if(ans == 0){
            printf("Impossible\n");
        }else{
            printf("%d\n",ans);
        }
    }
    
    return 0;
}
