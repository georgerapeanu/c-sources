#include <iostream>
#define KMAX 10
#define NMAX 100005
using namespace std;
int N,K;
int V[NMAX];
const int ceva=(1<<18);
int maxim;
bool pot[2][105][ceva+5];
void combinari(int pas,int rez,int prev)
{
    if(pas>N-K)
        maxim=max(maxim,rez);
    else
    {
        for(int i=prev+1;i<=K+pas;i++)
        {
            combinari(pas+1,rez|V[i],i);
        }
    }
}
void sautotal()
{
    int rez=0;
    for(int i=1;i<=N;i++)
        rez|=V[i];
    cout<<rez;
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    if(K<=7)
    {
        if(N>30+K)
        {
            sautotal();
        }
        else
        {
            combinari(1,0,0);
            cout<<maxim;
        }
    }
    else
    {
        if(N-K>17)
            sautotal();
        else
        {
            for(int i=0;i<=N;i++)
            {
                if(i<=K)
                    pot[i%2][i][0]=1;
                for(int j=0;j<=i,j<=K;j++)
                {
                    for(int k=0;k<=maxim;k++)
                    {
                        if(pot[i%2][j][k])
                        {
                            if(j<K)
                                pot[(i+1)%2][j+1][k]=1;
                            pot[(i+1)%2][j][(k|V[i+1])]=1;
                            if((k|V[i+1])>maxim)
                                maxim=k|V[i+1];
                        }
                    }
                }
            }
            int rmax=0;
            for(int i=1;i<=maxim;i++)
                if(pot[N%2][K][i])
                    rmax=i;
            cout<<rmax;
        }
    }
    return 0;
}
/*
10 8
1
2
3
4
5
6
7
8
9
10
corectanswer:5,10->15
*/
