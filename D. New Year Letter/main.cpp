#include <iostream>
#include <cstring>
using namespace std;
long long F[55];
int dp[55][4][4];
int N,M,K,x;
char A[105];
char B[105];
void baga(char C[],int st,int dr,int cat,int conf)
{
    if(conf&1)C[st++]='C';
    if(conf>>1)C[dr--]='A';
    while(cat--)
    {
        C[st]='A';
        C[st+1]='C';
        st+=2;
    }
}
int main()
{
    F[1]=F[2]=1;
    for(int i=3;i<=50;i++)F[i]=F[i-1]+F[i-2];
    cin>>K>>x>>N>>M;
    dp[3][2][1]=dp[3][2][3]=dp[3][3][1]=dp[3][3][3]=1;
    for(int i=4;i<=K;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                dp[i][j][k]=dp[i-2][j][k]+dp[i-1][j][k];
                if(i%2==0)
                {
                    if(((k>>1)&1)&&(j&1))dp[i][j][k]++;
                }
                else
                {
                    if(((k>>1)&1)&&(k&1))dp[i][j][k]++;
                }
            }
        }
    }
    int cat1,cat2;
    for(int k=0;k<4-(N==1);k++)
    {
        cat1=N;
        if(k==1||k==2)cat1--;
        if(k==3)cat1-=2;
        for(int l=0;l<4-(M==1);l++)
        {
            cat2=M;
            if(l==1||l==2)cat2--;
            if(l==3)cat2-=2;
            for(int i=0;i<=cat1/2&&F[K-2]*i<=x;i++)
            {
                int tmp=x-dp[K][k][l]-F[K-2]*i;
                if(tmp%F[K-1]==0&&0<=tmp/F[K-1]&&tmp/F[K-1]<=cat2/2)
                {
                    int j=tmp/F[K-1];
                    memset(A,'B',sizeof(A));
                    memset(B,'B',sizeof(B));
                    baga(A,1,N,i,k);
                    baga(B,1,M,j,l);
                    A[N+1]='\0';
                    B[M+1]='\0';
                    cout<<A+1<<"\n"<<B+1;
                    return 0;
                }
            }
        }
    }
    cout<<"Happy new year!";
    return 0;
}
