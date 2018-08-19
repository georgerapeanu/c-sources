#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("prieteni3.in","r"),*g=fopen("prieteni3.out","w");
vector <int> prieteni[110];
int n,A,k,nrp,nr,i,j,rank[110];
void bfs(int nod,int ran)
{
    for(vector<int> ::iterator it=prieteni[nod].begin();it!=prieteni[nod].end();it++)
    {
        if(!rank[*it]&&*it!=A)
        {
            rank[*it]=ran+1;
        }
    }
    for(vector<int> ::iterator it=prieteni[nod].begin();it!=prieteni[nod].end();it++)
    {
        if(rank[*it]==ran+1)
        {
            bfs(*it,ran+1);
        }
    }
}
int main()
{
    fscanf(f,"%d%d%d",&n,&A,&k);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&nrp);
        for(j=1;j<=nrp;j++)
        {
            fscanf(f,"%d",&nr);
            prieteni[i].push_back(nr);
        }
    }
    rank[A]=0;
    bfs(A,0);
    nr=0;
    for(i=1;i<=n;i++)
    {
        if(rank[i]==k)
        {
            nr++;
        }
    }
    fprintf(g,"%d\n",nr);
    for(i=1;i<=n;i++)
    {
        if(rank[i]==k)
        {
            fprintf(g,"%d ",i);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}

