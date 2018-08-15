#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
FILE *f = fopen("ro.in","r");
FILE *g = fopen("ro.out","w");
struct nod{
    bool single;
    int node;
    vector<int> bicco;
}V[5000];
vector<int> T[5000];
vector<int> G[3000];
int low[3000];
int h[3000];
vector<vector<int> > Bicco;
bool critice[3000];
int N,M;
int S[3000];
stack<pair<int,int> > st;
vector<int> tmp;
void dfsBicco(int nod,int tata){
    low[nod] = h[nod] = 1 + h[tata];
    for(auto it:G[nod]){
        if(it == tata){
            continue;
        }
        if(!h[it]){
            st.push({nod,it});
            dfsBicco(it,nod);
            low[nod] = min(low[nod],low[it]);
            if(low[it] >= h[nod]){
                critice[nod] = 1;
                tmp.clear();
                while(st.top().first != nod || st.top().second != it){
                    tmp.push_back(st.top().first);
                    tmp.push_back(st.top().second);
                    st.pop();
                }
                tmp.push_back(st.top().first);
                tmp.push_back(st.top().second);
                st.pop();
                sort(tmp.begin(),tmp.end());
                tmp.resize(unique(tmp.begin(),tmp.end()) - tmp.begin());
                Bicco.push_back(tmp);
            }
        }
        else{
            low[nod] = min(low[nod],h[it]);
        }
    }
}
long long dp1[4020][2];
long long dp2[4020][1 << 13];
int incomp[2010];
vector<int> comp;
bool valid(int mask){
    for(auto it:comp){
        for(auto it2:G[it]){
            if(incomp[it2]){
                if(((mask >> incomp[it]) & 1) + ((mask >> incomp[it2]) & 1) == 0){
                    return 0;
                }
            }
        }
    }
    return 1;
}
void dfs(int nod,int tata){
    for(auto it:T[nod]){
        if(it != tata){
            dfs(it,nod);
        }
    }
    if(V[nod].single){
        dp1[nod][1] = S[V[nod].node];
        for(auto it:T[nod]){
            if(it != tata){
                long long tmp1 = 1LL << 60;
                long long tmp2 = 1LL << 60;
                int pos = find(V[it].bicco.begin(),V[it].bicco.end(),V[nod].node) - V[it].bicco.begin();
                for(int mask = (1 << pos);mask < (1 << V[it].bicco.size());mask = (mask + 1) | (1 << pos)){
                    if(dp2[it][mask] < tmp1){
                        tmp1 = dp2[it][mask];
                    }
                    if(dp2[it][mask ^ (1 << pos)] < tmp2){
                        tmp2 = dp2[it][mask ^ (1 << pos)];
                    }
                    tmp2 = min(tmp2,dp2[it][mask ^(1 << pos)]);
                }
                dp1[nod][1] += tmp1 - S[V[nod].node];
                dp1[nod][0] += tmp2;
            }
        }
    }
    else{
        memset(incomp,0,sizeof(incomp));
        comp.assign(V[nod].bicco.begin(),V[nod].bicco.end());
        for(int i = 0;i < (int)comp.size();i++){
            incomp[comp[i]] = i;
        }
        for(int mask = 0; mask < (1 << V[nod].bicco.size());mask++){
            if(valid(mask)){
                for(int i = 0;i < (int)V[nod].bicco.size();i++){
                    if(critice[V[nod].bicco[i]] && V[tata].node != V[nod].bicco[i]){
                        dp2[nod][mask] += dp1[V[nod].bicco[i] + (int)Bicco.size()][(mask >> i) & 1];
                    }
                    else if((mask >> i) & 1){
                        dp2[nod][mask] += S[V[nod].bicco[i]];
                    }
                }
            }
            else{
                dp2[nod][mask] = 1LL << 60;
            }
        }
    }
}
vector<int> R;
void re(int nod,int tata,int wh){
    if(V[nod].single){
        dp1[nod][1] = S[V[nod].node];
        for(auto it:T[nod]){
            if(it != tata){
                long long tmp1 = 1LL << 60,ind1 = 0;
                long long tmp2 = 1LL << 60,ind2 = 0;
                int pos = find(V[it].bicco.begin(),V[it].bicco.end(),V[nod].node) - V[it].bicco.begin();
                for(int mask = (1 << pos);mask < (1 << V[it].bicco.size());mask = (mask + 1) | (1 << pos)){
                    if(dp2[it][mask] < tmp1){
                        tmp1 = dp2[it][mask];
                        ind1 = mask;
                    }
                    if(dp2[it][mask ^ (1 << pos)] < tmp2){
                        tmp2 = dp2[it][mask ^ (1 << pos)];
                        ind2 = mask ^ (1 << pos);
                    }
                }
                if(wh == 1){
                    re(it,nod,ind1);
                }
                else {
                    re(it,nod,ind2);
                }
            }
        }
    }
    else{
        int mask = wh;
        for(int i = 0;i < (int)V[nod].bicco.size();i++){
            if(critice[V[nod].bicco[i]] && V[tata].node != V[nod].bicco[i]){
                re(V[nod].bicco[i] + (int)Bicco.size(),nod,(mask >> i) & 1);
            }
            if((mask >> i) & 1){
                R.push_back(V[nod].bicco[i]);
            }
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&S[i]);
    }
    while(M--){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfsBicco(1,0);
    for(int i = 1;i <= (int)Bicco.size();i++){
        V[i].single = 0;
        V[i].node = 0;
        V[i].bicco.assign(Bicco[i - 1].begin(),Bicco[i - 1].end());
        for(auto it:Bicco[i - 1]){
            if(critice[it]){
                T[i].push_back(it + Bicco.size());
                T[it + Bicco.size()].push_back(i);
            }
        }
    }
    for(int j = 1;j <= N;j++){
        V[j + Bicco.size()].single = 1;
        V[j + Bicco.size()].node = j;
        V[j + Bicco.size()].bicco.clear();
    }
    dfs(1 + Bicco.size(),0);
    if(dp1[1 + Bicco.size()][1] < dp1[1 + Bicco.size()][0]){
        fprintf(g,"%lld\n",dp1[1 + Bicco.size()][1]);
        re(1 + Bicco.size(),0,1);
    }
    else {
        fprintf(g,"%lld\n",dp1[1 + Bicco.size()][0]);
        re(1 + Bicco.size(),0,0);
    }
    sort(R.begin(),R.end());
    R.resize(unique(R.begin(),R.end()) - R.begin());
    fprintf(g,"%d\n",(int)R.size());
    for(auto it:R){
        fprintf(g,"%d ",it);
    }
    fclose(f);
    fclose(g);
    return 0;
}
