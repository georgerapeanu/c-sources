#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#define LEN 4096
using namespace std;
FILE *f=fopen("java.in","r");
FILE *g=fopen("java.out","w");
int T,N,M,E;
vector<int> G[10001];
int L[10001];
int R[10001];
bitset<10001> U;
int nr;
bool ok;
int ind=LEN-1;
char buffer[LEN];
char getch()
{
    ind++;
    if(ind==LEN)
    {
        fread(buffer,1,4096,f);
        ind=0;
    }
    return buffer[ind];
}
int u32()
{
    int nr=0;
    char c='\0';
    while(!isdigit(c))c=getch();
    while(isdigit(c)) nr=nr*10+c-'0',c=getch();
    return nr;
}
bool pairup(int x)
{
    if(U[x])
        return 0;
    U[x]=1;
    for(auto it:G[x])
    {
        if(!R[it])
        {
            R[it]=x;
            L[x]=it;
            return 1;
        }
    }
    for(auto it:G[x])
    {
        if(pairup(R[it]))
        {
            R[it]=x;
            L[x]=it;
            return 1;
        }
    }
    return 0;
}
int main()
{
    T=u32();
    while(T)
    {
        nr=0;
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
       N=u32();M=u32();E=u32();
        for(int i=1;i<=N;i++) G[i].clear();
        for(int i=1;i<=E;i++)
        {
            int x,y;
            x=u32();y=u32();
            G[x].push_back(y);
        }
        do
        {
            U.reset();
            ok=0;
            for(int i=1;i<=N;i++)
            {
                if(L[i]) continue;
                if(pairup(i))
                    ok=1,nr++;
            }
        }
        while(ok);
        fprintf(g,"%d\n",nr);
        T--;
    }
    return 0;
}
