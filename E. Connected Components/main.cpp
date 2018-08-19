#include <cstdio>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;
unordered_set<int> S;
unordered_set<long long> E;
int N,M;
pair<int,int> V[200005];
int gr[200005];
bool viz[200005];
vector<int> tmp;
long long hsh(int x,int y){
    return 1LL * (N + 2) * x + y;
}
int propag(int nod){
    viz[nod] = 1;
    vector<int> toErase;
    int w = 1;
    for(auto it:S){
        if(!E.count(hsh(nod,it)) && !E.count(hsh(it,nod))){
            toErase.push_back(it);
        }
    }
    for(auto it:toErase){
        S.erase(it);
    }
    for(auto it:toErase){
        w += propag(it);
    }
    return w;
}
int main()
{
    scanf("%d %d",&N,&M);
    for(int i = 1;i <= M;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        gr[x]++;
        gr[y]++;
        E.insert(hsh(x,y));
    }
    for(int i = 1;i <= N;i++){
        V[i] = {gr[i],i};
        S.insert(i);
    }
    sort(V + 1,V + 1 + N);
    for(int i = N;i;i--){
        if(!viz[V[i].second]){
            S.erase(V[i].second);
            tmp.push_back(propag(V[i].second));
        }
    }
    sort(tmp.begin(),tmp.end());
    printf("%d\n",tmp.size());
    for(auto it:tmp){
        printf("%d ",it);
    }
    return 0;
}
