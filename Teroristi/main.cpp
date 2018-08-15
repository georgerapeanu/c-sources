#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
FILE *f=fopen("teroristi.in","r");
FILE *g=fopen("teroristi.out","w");
vector<int> G[1000];
int S=998;
int D=999;
int N,M;
bool viz[1000];
int C[1000][1000];
int F[1000][1000];
int stq,drq,Q[1000];
int T[1000];
char c[1000005];
int fr1[30];
int fr2[30][30];
pair<char,char> V[1000005];
map<pair<int,int>,vector<int> > tmp;
bool BFS(int S,int D)
{
    stq=drq=1;
    Q[1]=S;
    memset(viz,0,sizeof(viz));
    viz[S]=1;
    while(stq<=drq)
    {
        int nod=Q[stq++];
        if(nod==D)continue;
        for(auto it:G[nod])
        {
            if(!viz[it]&&F[nod][it]<C[nod][it])
            {
                viz[it]=1;
                T[it]=nod;
                Q[++drq]=it;
            }
        }
    }
    return viz[D];
}
int maxflow(int S,int D)
{
    int flow=0;
    while(BFS(S,D))
    {
        for(auto it:G[D])
        {
            if(viz[it]&&F[it][D]<C[it][D])
            {
                int fmin=1<<30;
                T[D]=it;
                for(int nod=D;nod!=S;nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                if(!fmin)continue;
                for(int nod=D;nod!=S;nod=T[nod]){F[T[nod]][nod]+=fmin;F[nod][T[nod]]-=fmin;}
                flow+=fmin;
            }
        }
    }
    return flow;
}
int has(int i,int j)
{
    return 30+30*i+j;
}
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    fgets(c+1,100,f);
    for(int i=1;i<=N;i++)fr1[c[i]-'a']++;
    for(int i=1;i<=M;i++)
    {
        char x,y;
        fscanf(f,"%c %c\n",&x,&y);
        if(x>y)swap(x,y);
        fr2[x-'a'][y-'a']++;
        V[i]={x,y};
        tmp[V[i]].push_back(i);
    }
    for(int i=0;i<='z'-'a';i++)
    {
        C[i][D]=fr1[i];
        G[D].push_back(i);
        G[i].push_back(D);
        for(int j=0;j<='z'-'a';j++)
        {
           C[has(i,j)][i]=1<<25;G[has(i,j)].push_back(i);G[i].push_back(has(i,j));
           C[has(i,j)][j]=1<<25;G[has(i,j)].push_back(j);G[j].push_back(has(i,j));
           C[S][has(i,j)]=fr2[i][j];G[S].push_back(has(i,j));G[has(i,j)].push_back(S);
        }
    }
    maxflow(S,D);
    for(int i=1;i<=N;i++)
    {
        for(int j=0;j<='z'-'a';j++)
        {
            for(int k=0;k<='z'-'a';k++)
            {
                if(F[has(j,k)][c[i]-'a']>0)
                {
                    F[has(j,k)][c[i]-'a']--;
                    fprintf(g,"%d ",tmp[{j+'a',k+'a'}].back());
                    tmp[{j+'a',k+'a'}].pop_back();
                    k='z'+1;j='z'+1;
                }
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
