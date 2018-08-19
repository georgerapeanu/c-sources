#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#define vecin first
#define distanta second
#define inf 999999999
using namespace std;
FILE *f=fopen("dragoni.in","r");
FILE *g=fopen("dragoni.out","w");
int N,M,P,Dmax[805],i,a,b,c,maxim,j;
int D[805][805];
vector <pair<int,int> > V[805];
bitset <806> U;
int dragon,insula;
int main()
{
    fscanf(f,"%d%d%d",&P,&N,&M);
    if(P==1)
    {
        for(i=1;i<=N;i++)
            fscanf(f,"%d",&Dmax[i]);
        for(i=1;i<=M;i++)
        {
            fscanf(f,"%d %d %d",&a,&b,&c);
            if(c<=Dmax[1])
            {
                V[a].push_back(make_pair(b,c));
                V[b].push_back(make_pair(a,c));
            }
        }
        queue <int> Q;
        U[1]=1;
        Q.push(1);
        maxim=Dmax[1];
        while(!Q.empty())
        {
            a=Q.front();
            Q.pop();
            for(vector<pair<int,int> > ::iterator it=V[a].begin();it!=V[a].end();it++)
            {
                if(!U[(*it).first])
                {
                    Q.push((*it).first);
                    U[(*it).first]=1;
                    if(Dmax[(*it).first]>maxim)
                        maxim=Dmax[(*it).first];
                }
            }
        }
        fprintf(g,"%d",maxim);
    }
    else
    {
        for(i=1;i<=N;i++)
            fscanf(f,"%d",&Dmax[i]);
        for(i=1;i<=M;i++)
        {
            fscanf(f,"%d %d %d",&a,&b,&c);
            V[a].push_back(make_pair(b,c));
            V[b].push_back(make_pair(a,c));
        }
        queue < pair<int,int> > Q;
        Q.push(make_pair(1,1));
        for(i=1;i<=N;i++)
            for(j=1;j<=N;j++)
                D[i][j]=inf;
        D[1][1]=0;
        while(!Q.empty())
        {
            dragon=(Q.front()).second;
            insula=(Q.front()).first;
            Q.pop();
            for(vector<pair<int,int> > ::iterator it=V[insula].begin();it!=V[insula].end();it++)
            {
                if((*it).second<=Dmax[dragon]&&D[insula][dragon]+(*it).second<D[(*it).first][dragon])
                {
                    Q.push(make_pair((*it).first,dragon));
                    D[(*it).first][dragon]=D[insula][dragon]+(*it).second;
                }
            }
            if(insula!=dragon&&D[insula][insula]>D[insula][dragon])
            {
                Q.push(make_pair(insula,insula));
                D[insula][insula]=D[insula][dragon];
            }
        }
        maxim=D[N][1];
        for(i=2;i<=N;i++)
            if(maxim>D[N][i])
                maxim=D[N][i];
        fprintf(g,"%d",maxim);
    }
    fclose(f);
    fclose(g);
    return 0;
}
