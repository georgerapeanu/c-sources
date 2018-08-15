#include <cstdio>
#include <iostream>
#include <algorithm>
#define MOD 3210121
using namespace std;
FILE *f=fopen("cowfood.in","r");
FILE *g=fopen("cowfood.out","w");;
int N,K,S,ans;
int A[25][35];
int C[10035][35];
int tmp[35];
void btr(int pas,int sgn,bool baga)
{
    if(pas>N)
    {
        if(!baga)return ;
        int s=S;
        for(int i=1;i<=K;i++)s-=tmp[i];
        if(s<0)return ;
        ans+=sgn*C[s+K][K];
        if(ans<0)ans+=MOD;
        if(ans>=MOD)ans-=MOD;
        return ;
    }
    btr(pas+1,sgn,baga);
    int ant[35];
    for(int i=1;i<=K;i++)
    {
        ant[i]=tmp[i];
        tmp[i]=max(tmp[i],A[pas][i]);
    }
    btr(pas+1,sgn*-1,1);
    for(int i=1;i<=K;i++)tmp[i]=ant[i];
}
int main()
{
    fscanf(f,"%d%d%d",&K,&S,&N);
    for(int i=1;i<=N;i++)for(int j=1;j<=K;j++)fscanf(f,"%d",&A[i][j]);
    for(int i=0;i<=S+K;i++)
    {
        C[i][0]=1;if(i<=K)C[i][i]=1;
        for(int j=1;j<i&&j<=K;j++)
        {
            C[i][j]=C[i-1][j]+C[i-1][j-1];
            if(C[i][j]>=MOD)C[i][j]-=MOD;
        }
    }
    ans=C[S+K][K]-1-K*S;
    btr(1,1,0);
    fprintf(g,"%d",ans);
    fclose(f);
    fclose(g);
    return 0;
}
