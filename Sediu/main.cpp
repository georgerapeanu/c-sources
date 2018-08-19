#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("sediu.in","r");
FILE *g=fopen("sediu.out","w");
int minim=(1<<30);
vector<int> G[16001];
int N;
int rez[16001];
int w(int nod,int tata)
{
    int weight=1,f=0,tmp=0;
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            f=w(it,nod);
            tmp=max(f,tmp);
            weight+=f;
        }
    }
    tmp=max(tmp,N-weight);
    if(minim>tmp)
        minim=tmp,rez[0]=0;
    if(minim==tmp)
        rez[++rez[0]]=nod;
    return weight;
}
int main()
{
    fscanf(f,"%d",&N);
    int x,y;
    for(int i=1;i<N;i++)
    {
        fscanf(f,"%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    w(1,0);
    sort(rez+1,rez+1+rez[0]);
    fprintf(g,"%d %d\n",minim,rez[0]);
    for(int i=1;i<=rez[0];i++) fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
