#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
struct Edge{
    int to;
    long long w;
    bool operator < (const Edge &other)const{
        return w > other.w;
    }
};
vector<Edge> G[200005];
priority_queue<Edge> H;
long long d[200005];
long long a[200005];
int N,M;
int main()
{
    scanf("%d %d",&N,&M);
    while(M--){
        long long x,y,w;
        scanf("%I64d %I64d %I64d",&x,&y,&w);
        G[x].push_back({y,w});
        G[y].push_back({x,w});
    }
    for(int i = 1;i <= N;i++){
        scanf("%I64d",&a[i]);
        H.push({i,a[i]});
        d[i] = a[i];
    }
    while(!H.empty()){
        Edge tmp = H.top();H.pop();
        if(tmp.w == d[tmp.to]){
            for(auto it:G[tmp.to]){
                if(it.w * 2 + tmp.w < d[it.to]){
                    d[it.to] = it.w * 2 + tmp.w;
                    H.push({it.to,it.w * 2 + tmp.w});
                }
            }
        }
    }
    for(int i = 1;i <= N;i++){
        printf("%I64d ",d[i]);
    }
    return 0;
}
