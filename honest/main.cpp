#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
FILE *f=fopen("honest.in","r");
FILE *g=fopen("honest.out","w");
queue <int> Q;
vector <int> O;
vector <int> G[1005];
bool viz[1005];
bool C[1005],swa;
int nr;
int i,N,M,a,b,in[1005];
char c;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %c %d",&a,&c,&b);
        G[a].push_back(b*10+(c=='c'));
        in[b]++;
    }
    for(i=1;i<=N;i++)
    {
        if(in[i]==0)
            {Q.push(i);viz[i]=1;}
    }
    while(!Q.empty())
    {
        O.push_back(Q.front());
        for(vector <int> :: iterator it=G[Q.front()].begin();it!=G[Q.front()].end();it++)
        {
            if(!viz[(*it)/10])
            {
                in[(*it)/10]--;
                if(in[(*it)/10]==0)
                    {Q.push((*it)/10);viz[(*it)/10]=1;}
            }
        }
        Q.pop();
    }
    for(i=1;i<=N;i++)
        viz[i]=0;
    for(vector <int> :: iterator it=O.begin();it!=O.end();it++)
    {
        if(!viz[(*it)])
        {
            viz[(*it)]=1;
            C[(*it)]=1;
            nr++;
            Q.push((*it));
            while(!Q.empty())
            {
                for(vector <int> :: iterator it2=G[Q.front()].begin();it2!=G[Q.front()].end();it2++)
                {
                    C[(*it2)/10]=!(C[Q.front()]^((*it2)%10));
                    nr+= C[(*it2)/10];
                    viz[(*it2)/10]=1;
                }
                Q.pop();
            }
        }
    }
    if(nr<N/2+N%2)
        swa=1;
    for(i=1;i<=N;i++)
    {
        fprintf(g,"%d\n",swa^C[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
