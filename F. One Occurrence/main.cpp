#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N,Q;
int A[500005];
vector< pair<int,int> > querys[500005];
vector<int> positions[500005];
int ans[500005];
int AINT[2000005];

void u(int nod,int st,int dr,int pos,int val){
    if(st > pos || dr < pos){
        return ;
    }

    if(st == dr){
        AINT[nod] = val;
        return ;
    }

    int mid = (st + dr) / 2;
    u(nod * 2,st,mid,pos,val);
    u(nod * 2 + 1,mid + 1,dr,pos,val);
    AINT[nod] = max(AINT[2 * nod],AINT[2 * nod + 1]);
}

int q(int nod,int st,int dr,int S,int D){
    if(dr < S || st > D){
        return 0;
    }

    if(S <= st && dr <= D){
        return AINT[nod];
    }
    int mid = (st + dr) / 2;
    return max(q(nod * 2,st,mid,S,D),q(nod * 2 + 1,mid + 1,dr,S,D));
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        scanf("%d",&A[i]);
    }
    scanf("%d",&Q);
    for(int i = 1;i <= Q;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        querys[x].push_back({y,i});
    }

    for(int i = N;i;i--){
        positions[A[i]].push_back(i);
    }

    for(int i = 1;i <= 5e5;i++){
        if(positions[i].size()){
            u(1,1,N,positions[i].back(),(positions[i].size() > 1 ? positions[i][positions[i].size() - 2] : N + i));
        }
    }

    for(int i = 1;i <= N;i++){
        for(auto it:querys[i]){
            ans[it.second] = q(1,1,N,i,it.first);
            if(ans[it.second] <= it.first){
                ans[it.second] = 0;
            }
            else if(ans[it.second] > N){
                ans[it.second] -= N;
            }
            else{
                ans[it.second] = A[ans[it.second]];
            }
        }
        u(1,1,N,positions[A[i]].back(),0);
        positions[A[i]].pop_back();
        if(positions[A[i]].size()){
            u(1,1,N,positions[A[i]].back(),(positions[A[i]].size() > 1 ? positions[A[i]][positions[A[i]].size() - 2] : N + A[i]));
        }
    }

    for(int i = 1;i <= Q;i++){
        printf("%d\n",ans[i]);
    }

    return 0;
}
