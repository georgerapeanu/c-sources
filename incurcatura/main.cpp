#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("incurcatura.in","r");
FILE *g=fopen("incurcatura.out","w");
int P;
int N;
int gr[100005];
vector<int> I[1000005];
vector<int> E[1000005];
vector<int> S,V;
int main()
{
    fscanf(f,"%d",&P);
    fscanf(f,"%d",&N);
    V.resize(N+2);
    for(int i=1;i<=N;i++)
    {
        int K;
        fscanf(f,"%d",&K);
        gr[i]-=K;
        S.push_back(i);
        for(int j=1;j<=K;j++)
        {
            int val;
            fscanf(f,"%d",&val);
            gr[val]++;
            E[i].push_back(val);
            I[val].push_back(i);
        }
    }
    if(P==1)
    {
        for(int i=1;i<=N;i++)
        {
            sort(E[i].begin(),E[i].end());
            sort(I[i].begin(),I[i].end());
            if(gr[i]>0)
            {
                set_intersection(I[i].begin(),I[i].end(),S.begin(),S.end(),V.begin());
                S.assign(V.begin(),V.end());
            }
            else if(gr[i]<0)
            {
                set_intersection(E[i].begin(),E[i].end(),S.begin(),S.end(),V.begin());
                S.assign(V.begin(),V.end());
            }
        }
        fprintf(g,"%d",S[0]);
    }
    else
    {
        for(int i=1;i<=N;i++)
        {
            if(gr[i]!=0)
                V.push_back(i);
        }
        int x,y;
        for(auto it:V)
        {
            if(gr[it]<0){x=it;break;}
        }
        for(auto it:V)
        {
            if(gr[it]>0){y=it;break;}
        }
        if(x>y)swap(x,y);
        fprintf(g,"%d %d",x,y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
