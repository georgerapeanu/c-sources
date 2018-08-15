#include <cstdio>
#include <cstring>
#define MOD 10000
using namespace std;
FILE *f=fopen("piramida.in","r");
FILE *g=fopen("piramida.out","w");
int S;
int C[20][20];
int nr[2][600001];
int main()
{
    for(int i=0;i<20;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    fscanf(f,"%d",&S);
    int h=0;
    while(S>>h)
        h++;
    h--;
    nr[0][0]=1;
    for(int coef=0;coef<=h;coef++)
    {
        for(int i=0;i<=S-C[h][coef];i++)
        {
            nr[1-coef%2][i+C[h][coef]]+=nr[coef%2][i]+nr[1-coef%2][i];
            nr[1-coef%2][i+C[h][coef]]%=MOD;
        }
        memset(nr[coef%2],0,sizeof(nr[coef%2]));
    }
    fprintf(g,"%d",nr[1-h%2][S]);
    fclose(f);
    fclose(g);
    return 0;
}
