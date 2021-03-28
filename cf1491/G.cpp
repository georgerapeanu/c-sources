#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;;

int n;
int v[NMAX + 5];
bool viz[NMAX + 5];
vector<vector<int> > cycles;

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i <= n;i++){
        if(i != v[i] && viz[i] == false){
            vector<int> cycle = {i};
            viz[i] = true;
            for(int nod = v[i];nod != i;nod = v[nod]){
                cycle.push_back(nod);
                viz[nod] = true;
            }
            cycles.push_back(cycle);
        }
    }

    vector<pair<int,int> > ans;

    while((int)cycles.size() > 1){
        vector<int> fst = cycles.back();cycles.pop_back();
        vector<int> snd = cycles.back();cycles.pop_back();
        ans.push_back({fst.back(),snd[0]});
        for(int i = 1;i < (int)snd.size();i++){
            ans.push_back({fst.back(),snd[i]});
        }
        for(int i = 0;i < (int)fst.size() - 1;i++){
            ans.push_back({snd[0],fst[i]});
        }
        ans.push_back({fst.back(),snd[0]});
    }

    if((int)cycles.size() == 1){
        vector<int> cycle = cycles.back();cycles.pop_back();
        if((int)cycle.size() == 2){
            int tmp = 1;
            while(cycle[0] == tmp || cycle[1] == tmp){
                tmp++;
            }
            for(int i = 0;i < (int)cycle.size();i++){
                ans.push_back({cycle[i],tmp});
            }
            ans.push_back({cycle[0],tmp});
        }else{
            ans.push_back({cycle[0],cycle[(int)cycle.size() - 1]});
            for(int i = 1;i < (int)cycle.size() - 2;i++){
                ans.push_back({cycle[i],cycle.back()});
            }
            vector<int> reduced_cycle = {cycle[0],cycle[(int)cycle.size() - 2],cycle.back()};
            ans.push_back({reduced_cycle[0],reduced_cycle[1]});
            ans.push_back({reduced_cycle[1],reduced_cycle[2]});
            ans.push_back({reduced_cycle[0],reduced_cycle[2]});
        }
    }

    printf("%d\n",(int)ans.size());

    for(auto it:ans){
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
