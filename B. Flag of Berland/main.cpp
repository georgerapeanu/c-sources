#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int N,M;
char C[105][105];
char tmp[105][105];
int nr[105];
bool u[258];
bool ok()
{
    memset(nr,0,sizeof(nr));
    memset(u,0,sizeof(nr));
    bool ok=1;
    for(int i=1;i<=N;i++)
    {
        char c=C[i][1];
        for(int j=2;j<=M;j++)if(c!=C[i][j])ok=0;
        if(C[i][1]!=C[i-1][1])nr[0]++;
        u[c]=1;
        nr[nr[0]]++;
    }
    ok&=(nr[0]==3&&u['R']&&u['B']&&u['G']);
    for(int i=2;i<4;i++)ok&=(nr[i]==nr[i-1]);
    return ok;
}
int main()
{
    scanf("%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)fgets(C[i]+1,105,stdin);
    if(ok()){printf("YES");return 0;}
    for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)tmp[M-j+1][i]=C[i][j];
    memset(C,'\0',sizeof(C));
    swap(N,M);
    for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)C[i][j]=tmp[i][j];
    if(ok()){printf("YES");return 0;}
    printf("NO");
    return 0;
}
