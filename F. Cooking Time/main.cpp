#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
int T,N,K;
set<int> S;
map<int,int> M;
int V[100005];
int nxt[100005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        M.clear();
        S.clear();
        scanf("%d %d",&N,&K);
        int rez=0;
        for(int i=1;i<=N;i++)scanf("%d",&V[i]);
        for(int i=N;i;i--)
        {
            if(M.count(V[i]))
            {
                nxt[i]=M[V[i]];
            }
            else
            {
                nxt[i]=N+1;
            }
            M[V[i]]=i;
        }
        for(int i=1;i<=N;i++)
        {
            if(S.count(i))
            {
                S.erase(i);
                S.insert(nxt[i]);
            }
            else
            {
                rez++;
                if(S.size()<K)
                {
                    S.insert(nxt[i]);
                }
                else
                {
                    S.erase(*S.rbegin());
                    S.insert(nxt[i]);
                }
            }
        }
        printf("%d\n",rez);
    }
    return 0;
}
