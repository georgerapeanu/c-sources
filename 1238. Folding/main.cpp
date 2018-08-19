#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char C[105];
int rep[105][105];///de cate ori se repeta stringul de pe pozitia i de lungime l in substringul i....N
int t[105][105];
int dp[105][105];
int N,lung;
int nrcf(int nr)
{
    int cf=0;
    while(nr)
    {
        nr/=10;
        cf++;
    }
    return cf;
}
void printans(int st,int dr)
{
    if(st==dr)
    {cout<<C[st];return ;}
    if(t[st][dr]<0)
    {
        char tmp[105];
        sprintf(tmp,"%d",(st-dr-1)/t[st][dr]);
        int len=nrcf((st-dr-1)/t[st][dr]);
        for(int i=0;i<len;i++)
            cout<<tmp[i];
        cout<<"(";
        printans(st,st-t[st][dr]-1);
        cout<<")";
    }
    else if(!t[st][dr])
    {
        for(int i=st;i<=dr;i++)
            cout<<C[i];
    }
    else
    {
        printans(st,t[st][dr]);
        printans(t[st][dr]+1,dr);
    }
}
int main()
{
    cin.getline(C+1,105);
    N=strlen(C+1);
    for(int k=1;k<=N;k++)
        for(int i=N-k+1;i>0;i--)
            rep[i][k]=(strncmp(C+i,C+i+k,k)==0 ? rep[i+k][k]:0)+1;
    for(int i=N;i>0;i--)
    {
        for(int j=i;j<=N;j++)
        {
            dp[i][j]=lung=j-i+1;
            for(int l=1;l<lung;l++)
            {
                if(min(rep[i][l],lung/l)*l==lung)///de cate ori se repeta poate fi mai mult decat de cate ori intra,dar totusi e corect
                {
                    if(dp[i][j]>2+dp[i][i+l-1]+nrcf(lung/l))
                    {
                        dp[i][j]=2+dp[i][i+l-1]+nrcf(lung/l);
                        t[i][j]=-l;
                    }
                }
            }
            for(int k=i;k<j;k++)
            {
                if(dp[i][j]>dp[i][k]+dp[k+1][j])
                {
                    dp[i][j]=dp[i][k]+dp[k+1][j];
                    t[i][j]=k;
                }
            }
        }
    }
    printans(1,N);
    return 0;
}
