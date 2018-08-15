#include <bits/stdc++.h>
#define inf 10000005
using namespace std;
char C[8005];
int i,j,N;
bool P[4005][4005];
int V[4005];
int T[4005];
void trans(int poz)
{
    for(int i=N+1;i>poz;i--)
        C[i]=C[i-1];
    N++;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin.getline(C+1,4005);
    N=strlen(C+1);
    for(i=1;i<=N;i++)
    {
        P[i][i]=1;
        if(C[i]==C[i+1])
            P[i][i+1]=1;
        for(j=1;j<i-1;j++)
        P[j][i]=(C[j]==C[i])&&P[j+1][i-1];
    }
    for(i=1;i<=N;i++)
    {
        V[i]=inf;
        for(j=1;j<=i;j++)
        {
            if(P[j][i])
            {
                if(V[i]>V[j-1]+1)
                {
                    V[i]=V[j-1]+1;
                    T[i]=j;
                }
            }
        }
    }
    cout<<V[N]<<"\n";
    i=N;
    while(i)
    {
        trans(T[i]);
        C[T[i]]=' ';
        i=T[i]-1;
    }
    cout<<C+2;
    return 0;
}
