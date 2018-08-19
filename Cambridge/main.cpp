#include <cstdio>
#include <algorithm>
using namespace std;
struct node{
    int min_index;
    int max_index;
    bool canDo;
    long long minDif;
    long long time;
    bool active;
};
int N,M;
pair<pair<int,int>,int> V[100005];
int R[100005];
int finalpos[100005];
node AINT[400005];
node join(node a,node b,node d){
    node c;
    a.min_index = b.min_index = c.min_index = d.min_index;
    a.max_index = b.max_index = c.max_index = d.max_index;
    if(!b.active && !a.active){
        c.active = 0;
        return c;
    }
    if(!b.active){
        return a;
    }
    if(!a.active){
        return b;
    }
    c.active = 1;
    c.canDo = (a.canDo && b.canDo && b.minDif > a.time);
    c.time = a.time + b.time;
    c.minDif = min(a.minDif,b.minDif - a.time);
    return c;
}
void build(int nod,int st,int dr){
    if(st == dr){
        AINT[nod].min_index = V[st].second;
        AINT[nod].max_index = V[st].second;
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    AINT[nod].min_index = min(AINT[2 * nod].min_index,AINT[2 * nod + 1].min_index);
    AINT[nod].max_index = max(AINT[2 * nod].max_index,AINT[2 * nod + 1].max_index);
}
void activate(int nod,int st,int dr,int pos,bool wut){
    if(pos < st || pos > dr){
        return ;
    }
    if(st == dr){
        AINT[nod].active = (!wut);
        AINT[nod].min_index = V[st].second;
        AINT[nod].max_index = V[st].second;
        AINT[nod].canDo = (V[st].first.second < V[st].first.first);
        AINT[nod].time = V[st].first.second;
        AINT[nod].minDif = V[st].first.first - V[st].first.second;
        return ;
    }
    int mid = (st + dr) / 2;
    activate(nod * 2,st,mid,pos,wut);
    activate(nod * 2 + 1,mid + 1,dr,pos,wut);
    AINT[nod] = join(AINT[2 * nod],AINT[2 * nod + 1],AINT[nod]);
}
int main(){
    scanf("%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        scanf("%d %d",&V[i].first.second,&V[i].first.first);
        V[i].second = i;
    }
    sort(V + 1,V + 1 + N);
    for(int i = 1;i <= N;i++){
        finalpos[V[i].second] = i;
    }
    build(1,1,N);
    int rightmost = 0;
    for(int left = 1;left <= N;left++){
        while((!AINT[1].active || AINT[1].canDo) && rightmost <= N){
            rightmost++;
            if(rightmost <= N){
                activate(1,1,N,finalpos[rightmost],0);
            }
        }
        R[left] = rightmost - 1;
        activate(1,1,N,finalpos[left],1);
    }
    while(M--){
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%d\n",R[x] >= y);
    }
    return 0;
}
