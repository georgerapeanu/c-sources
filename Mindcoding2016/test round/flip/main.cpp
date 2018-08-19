#include <cstdio>
#include <set>
#include <bitset>
using namespace std;
set<int> S;
bitset<100005> AIB;
bitset<100005> U;
int N,M;
void u(int pos)
{
    for(;pos<=N;pos+=(-pos)&pos)
        AIB[pos]=AIB[pos]^1;
}
int q(int pos)
{
    int nr=0;
    for(;pos;pos-=(-pos)&pos)
        nr^=AIB[pos];
    return nr;
}
int main()
{
    scanf("%d %d",&N,&M);
    S.insert(0);
    S.insert(N+1);
    for(int i=1;i<=M;i++)
    {
        int tip,x,y;
        scanf("%d",&tip);
        if(tip==1)
        {
            scanf("%d %d",&x,&y);
            u(x);u(y+1);
            if(U[x])S.erase(x);
            else S.insert(x);
            U[x]=U[x]^1;
            if(y!=N)
            {
                if(U[y+1])S.erase(y+1);
                else S.insert(y+1);
                U[y+1]=U[y+1]^1;
            }
        }
        else
        {
            scanf("%d",&x);
            set<int>::iterator it=S.lower_bound(x);
            if(*it>x)it--;
            int st=*it;
            it++;
            int dr=*it;
            if(!st)st++;
            printf("%d %d %d\n",q(x),st,dr-1);
        }
    }
    return 0;
}
