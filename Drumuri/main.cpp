#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
using namespace std;
FILE *f=fopen("drumuri.in","r");
FILE *g=fopen("drumuri.out","w");
int N,M;
vector<int> G[10004];
set<pair<int,int> > S;
bitset<10004> B;
void dfs(int nod,int tata)
{
     if(B[nod])return ;
     B[nod]=1;
     bool ceva=0;
     for(auto it:G[nod])dfs(it,nod);
     for(auto it:G[nod])
     {
         if(it==tata||S.find({nod,it})!=S.end()||S.find({it,nod})!=S.end())continue;
         if(!ceva){fprintf(g,"%d %d ",it,nod);ceva^=1;S.insert({it,nod});S.insert({nod,it});}
         else {fprintf(g,"%d\n",it);ceva^=1;S.insert({it,nod});S.insert({nod,it});}
     }
     if(ceva)
     {
         fprintf(g,"%d\n",tata);
        S.insert({tata,nod});S.insert({nod,tata});
     }
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    if(M%2==1){fputc('0',g);return 0;}
    fputs("1\n",g);
    dfs(1,0);
    return 0;
}
