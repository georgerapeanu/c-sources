#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
FILE *f=fopen("overlap.in","r");
FILE *g=fopen("overlap.out","w");
int N;
pair<int,int> A[805];
pair<int,int> V[805];
map<pair<int,int>,int> M;
int nxt[805];
int ant[805];
int cul[805];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
        M[V[i]]=i;
        A[i]=V[i];
    }
    for(int i=0;i<4;i++)
    {
        for(int j=1;j<=N;j++){swap(V[j].first,V[j].second);V[j].second*=-1;}
        for(int j=2;j<=N;j++)
        {
            bool ok=1;
            memset(cul,0,sizeof(cul));
            memset(ant,0,sizeof(ant));
            memset(nxt,0,sizeof(nxt));
            for(int k=1;k<=N;k++)
            {
                if(M.count({A[j].first-V[1].first+V[k].first,A[j].second-V[1].second+V[k].second})!=0)
                {
                    int t=M[{A[j].first-V[1].first+V[k].first,A[j].second-V[1].second+V[k].second}];
                    nxt[k]=t;
                    ant[t]=k;
                }
            }
            for(int k=1;k<=N&&ok;k++)
            {
                int nr=0,ind=k;
                while(ant[ind]&&ant[ind]!=k)
                    ind=ant[ind];
                while(!cul[ind]&&ind)
                {
                    cul[ind]=(nr&1)+1;
                    nr++;
                    ind=nxt[ind];
                }
                if(nr&1)ok=0;
            }
            if(ok)
            {
                for(int i=1;i<=N;i++)
                    fprintf(g,"%d\n",cul[i]);
                return 0;
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
