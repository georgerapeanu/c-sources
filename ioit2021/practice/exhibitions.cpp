#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n,m;
int a[NMAX + 5];
int p[NMAX + 5];
int g[NMAX + 5];
int _exp[NMAX + 5];
int ans[NMAX + 5];

vector<int> stuff[4];

bool cmp(int i,int j){
    return a[i] > a[j];
}

int main(){
    
    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        scanf("%d",&_exp[i]);
        _exp[i]++;
    }

    int best = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&a[i],&p[i],&g[i]);
        if(best == 0 || a[best] < a[i]){
            best = i;
        }
        int state = g[i] * 2 + p[i];
        stuff[state].push_back(i);
    }

    for(int k = 0;k < 4;k++){
        sort(stuff[k].begin(),stuff[k].end(),cmp);
    }

    for(int i = 1;i <= n;i++){
        if(g[i] == p[best]){
            ans[i] = p[best];
        }else{
            if(stuff[g[i] * 2].size() + stuff[g[i] * 2 + 1].size() == 1){
                ans[i] = 1 - g[i];
            }else{
                int fst_var = 0;
                int snd_var = (int)stuff[g[i] * 2 + 1 - g[i]].size() - 1;

                while(fst_var < (int)stuff[g[i] * 2 + g[i]].size() && stuff[g[i] * 2 + g[i]][fst_var] == i){
                    fst_var++;
                }
                if(fst_var >= (int)stuff[g[i] * 2 + g[i]].size()){
                    fst_var = -1;
                }else{
                    fst_var = stuff[g[i] * 2 + g[i]][fst_var];
                }
                
                while(snd_var >= 0 && stuff[g[i] * 2 + 1 - g[i]][snd_var] == i){
                    snd_var--;
                }

                if(snd_var < 0){
                    snd_var = -1;
                }else{
                    snd_var = stuff[g[i] * 2 + 1 - g[i]][snd_var];
                }

                bool ok_guide = false;

                if(fst_var != -1){
                    int best_values[] = {0,0};
                    best_values[p[i]] = a[i];
                    best_values[p[fst_var]] = max(best_values[p[fst_var]],a[fst_var]);
                    if(best_values[g[i]] > best_values[1 - g[i]]){
                        ok_guide = true;
                    }
                }
                if(snd_var != -1){
                    int best_values[] = {0,0};
                    best_values[p[i]] = a[i];
                    best_values[p[snd_var]] = max(best_values[p[snd_var]],a[snd_var]);
                    if(best_values[g[i]] > best_values[1 - g[i]]){
                        ok_guide = true;
                    }
                }

                if(ok_guide){
                    ans[i] = g[i];
                }else{
                    ans[i] = 1 - g[i]; 
                }
            }
        }
    }

    for(int i = 1;i <= m;i++){
        printf("%d ",ans[_exp[i]]);
    }

    return 0;
}
