#include <iostream>
#include <vector>
using namespace std;
bool E[1005];
int T,M;
int G[105][105];
int nr;
vector<int> P;
bool U[105];
int A[105];
void init(int A[],int val)
{
    A[0]=0;
    while(val){A[++A[0]]=val%10;val/=10;}
    A[0]=max(A[0],1);
}
void mult(int A[],int val)
{
    int t=0;
    for(int i=1;i<=A[0]||t;i++)
    {
        A[i]=val*A[i]+t;
        t=A[i]/10;
        A[i]%=10;
        A[0]=max(A[0],i);
    }
}
int main()
{
    P.push_back(0);
    E[0]=E[1]=1;
    for(int i=2;i<=1000;i++)
    {
        if(!E[i])
        {
            P.push_back(i);
            for(int j=i*i;j<=1000;j+=i)E[j]=1;
        }
    }
    cin>>T>>M;
    for(int i=1;i<=M;i++)
    {
        int val=0;
        cin>>val;
        for(int j=1;j<=T;j++)
        {
            while(val%P[j]==0)
            {
                val/=P[j];
                G[j][i]^=1;
            }
        }
    }
    int i=1,j=1;
    while(i<=T&&j<=M)
    {
        int k;
        for(k=i;k<=T;k++)
        {
            if(G[k][j]!=0)break;
        }
        if(k>T)
        {
            j++;
            continue;
        }
        for(int l=1;l<=M;l++)swap(G[i][l],G[k][l]);
        for(k=i+1;k<=T;k++)
        {
            if(G[k][j])
            {
                for(int l=1;l<=M;l++)
                {
                    G[k][l]^=G[i][l];
                }
            }
        }
        i++;j++;
    }
    nr=M;
    for(int i=T;i;i--)
    {
        for(int j=1;j<=M;j++)
        {
            if(G[i][j])
            {
                if(!U[j])nr--;
                U[j]=1;
                break;
            }
        }
    }
    init(A,1);
    for(int i=1;i<=nr;i++)
        mult(A,2);
    A[1]--;
    for(int i=A[0];i;i--)cout<<A[i];
    return 0;
}
