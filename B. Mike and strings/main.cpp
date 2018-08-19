#include <iostream>
#include <cstring>
using namespace std;
int N,M;
bool lafel(char A[],char B[],int i,int j)
{
    int tmp=M;
    while(tmp--)
    {
        if(A[i]!=B[j])return 0;
        i++;
        j++;
        if(i>M)i-=M;
        if(j>M)j-=M;
    }
    return 1;
}
char C[55][55];
int main()
{
    cin>>N;
    cin.getline(C[0],100);
    for(int i=1;i<=N;i++)
    {
        cin.getline(C[i]+1,100);
    }
    M=strlen(C[1]+1);M-=(C[1][M]=='\n');
    int rez=(1<<30);
    for(int i=1;i<=M;i++)
    {
        int cost=i-1;
        for(int j=2;j<=N;j++)
        {
            bool ok=0;
            for(int k=1;k<=M;k++)
            {
                if(lafel(C[1],C[j],i,k))
                {ok=1;cost+=k-1;break;}
            }
            if(!ok)
            {
                cout<<-1;
                return 0;
            }
        }
        rez=min(cost,rez);
    }
    cout<<rez;
    return 0;
}
