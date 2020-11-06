#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int n;
int pref[NMAX + 5];
vector<int> pos[NMAX + 5];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
   
        for(int i = 0;i <= n;i++){
            pos[i].clear();
            pref[i] = 1e9;
        }

        for(int i = 0;i <= n;i++){
            pos[i].push_back(0);
        }
    
        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            pos[val].push_back(i);
        }
        
        for(int i = 0;i <= n;i++){
            pos[i].push_back(n + 1);
        }
    
        for(int i = 0;i <= n;i++){
            pref[i] = 1e9;
        }
    
        for(int i = 0;i <= n;i++){
            int ma = 0;
            for(int j = 1;j < (int)pos[i].size();j++){
                ma = max(ma,pos[i][j] - pos[i][j - 1]);
            }
            pref[ma] = min(pref[ma],i);
        }
    
        for(int i = 1;i <= n;i++){
            pref[i] = min(pref[i],pref[i - 1]);
            printf("%d ",(pref[i] == 1e9 ? -1:pref[i]));
        }
        printf("\n");
    }

    return 0;
}
