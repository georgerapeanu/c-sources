#include <iostream>
#include <vector>
#define MOD 1000000007
using namespace std;
bool E[75];
int T,M;
int G[75][100005];
int nr;
vector<int> P;
int N;
int V[100005];
bool U[100005];
int main()
{
    P.push_back(0);
    E[0]=E[1]=1;
    for(int i=2;i<=70;i++)
    {
        if(!E[i])
        {
            P.push_back(i);
            for(int j=i*i;j<=70;j+=i)E[j]=1;
        }
    }
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    for(int i=1;i<(int)P.size();i++)
    {
        for(int j=1;j<=N;j++)
        {
            int e=0;
            while(V[j]%P[i]==0)
            {
                e^=1;
                V[j]/=P[i];
            }
            G[i][j]=e;
        }
    }
    int i=1,j=1;
    while(i<(int)P.size()&&j<=N)
    {
        int k=i;
        for(k=i;k<P.size();k++)
            if(G[k][j])
                break;
        if(k==P.size())
        {
            j++;
            continue;
        }
        for(int l=1;l<=N;l++)
            swap(G[k][l],G[i][l]);
        for(k=i+1;k<P.size();k++)
        {
            if(G[k][j])
            {
                for(int l=j;l<=N;l++)
                {
                    G[k][l]^=G[i][l];
                }
            }
        }
        i++;j++;
    }
    for(int i=1;i<(int)P.size();i++)
        for(int j=1;j<=N;j++)
            if(G[i][j])
            {
                U[j]=1;
                break;
            }
    int rez=1;
    for(int i=1;i<=N;i++)
    {
        if(!U[i])
        {
            rez+=rez;
            if(rez>=MOD)
            {
                rez-=MOD;
            }
        }
    }
    rez--;
    if(rez<0)
    {
        rez+=MOD;
    }
    cout<<rez;
    return 0;
}
