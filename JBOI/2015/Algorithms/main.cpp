#include <iostream>
#include <cstdio>
using namespace std;
int D1[100005][5];
int D2[100005][5][5];
int D3[100005][5][5][5];
string A[100005][5];
int N,T,M;
int rez;
int gaseste(int pos,string a)
{
    for(int i=1;i<=T;i++)if(A[pos][i]==a)return i;
    return -1;
}
int main()
{
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
    cin>>N>>T>>M;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=T;j++)
            cin>>A[i][j];
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=T;j++)
        {
            int t=gaseste(i-1,A[i][j]);
            if(t==-1)D1[i][j]=1;
            else D1[i][j]=1+D1[i-1][t];
            rez=max(rez,D1[i][j]);
        }
    }
    if(M==1){cout<<rez;return 0;}
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=T;j++)
        {
            int pos=gaseste(i-1,A[i][j]);
            for(int k=1;k<=T;k++)
            {
                if(pos!=-1)D2[i][j][k]=1+D2[i-1][pos][k];
                else
                {
                    int ii=i-1-D1[i-1][k];
                    int pos2=gaseste(ii,A[i][j]);
                    if(pos2==-1)D2[i][j][k]=1+D1[i-1][k];
                    else D2[i][j][k]=1+D2[i-1][k][pos2];
                }
                rez=max(rez,D2[i][j][k]);
            }
        }
    }
    if(M==2){cout<<rez;return 0;}
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=T;j++)
        {
            int pos=gaseste(i-1,A[i][j]);
            for(int k=1;k<=T;k++)
            {
                for(int l=1;l<=T;l++)
                {
                    if(pos!=-1)D3[i][j][k][l]=D3[i-1][pos][k][l]+1;
                    else
                    {
                        int ii=i-1-D1[i-1][k];
                        int pos2=gaseste(ii,A[i][j]);
                        if(pos2!=-1)
                        {
                            D3[i][j][k][l]=1+D3[i-1][k][pos2][l];
                        }
                        else
                        {
                            ii=i-1-D2[i-1][k][l];
                            pos2=gaseste(ii,A[i][j]);
                            if(pos2==-1)D3[i][j][k][l]=1+D2[i-1][k][l];
                            else D3[i][j][k][l]=1+D3[i-1][k][l][pos2];
                        }
                    }
                    rez=max(rez,D3[i][j][k][l]);
                }
            }
        }
    }
    cout<<rez;
    return 0;
}
