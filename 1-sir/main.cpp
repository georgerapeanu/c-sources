#include <cstdio>
using namespace std;
FILE *f=fopen("1-sir.in","r");
FILE *g=fopen("1-sir.out","w");
int N;
int P=0;
long long i,j,K;
int rez;
long long S;
int D[3][65550];
int abso(int x)
{
    if(x>0)
        return x;
    return -x;
}
int main()
{
    fscanf(f,"%d %lld",&N,&S);
    S=abso(S);
    K=N*(N-1)/2;
    if(S>K)
        {fprintf(g,"0");return 0;}
    D[1][0]=1;
    for(i=2;i<=N;i++)
    {
        for(j=0;j<K;j++)
        {
            D[P][j]=D[1-P][abso(j-i+1)]+D[1-P][j+i-1];
            D[P][j]%=194767;
        }
        P=1-P;
    }
    rez=D[1-P][S];
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
