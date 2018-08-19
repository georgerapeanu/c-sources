#include <cstdio>
#include <algorithm>
using namespace std;
int V[(1 << 17) + 1];
pair<int,int> H[(1 << 17) + 1];
pair<pair<int,int>,int> q[(1 << 18) + 1];
int R[(1 << 18) + 1];
int N,Q,last = 0;
int main()
{
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        scanf("%d",&H[i].first);
        H[i].second = i;
    }
    scanf("%d",&Q);
    for(int i = 1;i <= Q;i++){
        scanf("%d %d",&q[i].first.second,&q[i].first.first);
        q[i].second = i;
    }
    sort(H,H + N);
    sort(q,q + Q);
    for(int i = 1;i <= Q;i++){
        while(last <= N && H[last].first <= q[i].first.first){
            for(int mask = 0;mask <= N;mask = (mask + 1) | H[last].second){
                V[mask]++;
            }
            last++;
        }
        R[q[i].second] = N - V[q[i].first.second];
    }
    for(int i = 1;i <= Q;i++){
       printf("%d\n",R[i]);
    }
    return 0;
}
