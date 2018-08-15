#include <iostream>
using namespace std;
int rez=1<<30;
int fr[305];
int A[305][305];
int N,M;
int U[305];
int st[305];
int main()
{
    cin>>N>>M;rez=N;
    for(int i=1;i<=N;i++){for(int j=1;j<=M;j++)cin>>A[i][j];st[i]=1;fr[A[i][1]]++;}
    int spmax=0,maxi=0;
    for(int j=1;j<=M;j++)if(maxi<fr[j]){maxi=fr[j];spmax=j;}
    rez=maxi;
    for(int i=1;i<M;i++)
    {
        int spmax=0,maxi=0;
        for(int j=1;j<=M;j++)if(maxi<fr[j]){maxi=fr[j];spmax=j;}
        U[spmax]=1;
        for(int j=1;j<=N;j++)
        {
            fr[A[j][st[j]]]--;
            while(U[A[j][st[j]]]){st[j]++;}
            fr[A[j][st[j]]]++;
        }
        spmax=0;maxi=0;
        for(int j=1;j<=M;j++)if(maxi<fr[j]){maxi=fr[j];spmax=j;}
        rez=min(rez,maxi);
    }
    cout<<rez;
    return 0;
}
