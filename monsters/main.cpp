#include <iostream>
#include <cstdio>
using namespace std;
int N,M;
long long V[755][755];
int S[755][755];
char C[755][755];
long long total,rez;
void add(int stx,int sty,int drx,int dry,int val)
{
    V[stx][sty]+=val;
    V[drx+1][sty]-=val;
    V[stx][dry+1]-=val;
    V[drx+1][dry+1]+=val;
}
bool isfull(int col,int stx,int drx)
{
    return (drx-stx+1==S[drx][col]-S[stx-1][col]);
}
int main() {
    scanf("%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)fgets(C[i]+1,755,stdin);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            S[i][j]=S[i-1][j]+(C[i][j]=='1');
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=i;j<=N;j++)
        {
            for(int L=1,R=0;L<=M;L=max(R+1,L+1))
            {
                R=max(R,L-1);
                while(isfull(R+1,i,j))R++;
                for(int k=L;k<=R;k++)
                    add(i,k,j,k,(R-k+1)*(k-L+1));
                total+=(R-L+1)*(R-L+2)/2;
            }
        }
    }
    rez=total;
    //cerr<<total<<"\n";
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            V[i][j]=V[i-1][j]+V[i][j-1]-V[i-1][j-1]+V[i][j];
            rez=min(total-V[i][j],rez);
            //cerr<<V[i][j]<<" ";
        }
        //cerr<<"\n";
    }
    printf("%lld",rez);
    return 0;
}
