#include <cstdio>
FILE *f=fopen("nunta.in","r");
FILE *g=fopen("nunta.out","w");
int V[3][30];
int N,n,CB,t;
const int BASE=100000000;
void add()
{
    V[2][0]=0;
    if(V[0][0]>V[1][0])
        n=V[0][0];
    else
        n=V[1][0];
    t=0;
    for(int i=1;i<=n||t;i++)
    {
        V[2][i]=((i<=V[0][0] ? V[0][i]:0)+(i<=V[1][0] ? V[1][i]:0)+t);
        t=V[2][i]/BASE;
        V[2][i]%=BASE;
        V[2][0]++;
    }
}
void copiere()
{
    for(int i=0;i<=V[1][0];i++)
        V[0][i]=V[1][i];
    for(int i=0;i<=V[2][0];i++)
        V[1][i]=V[2][i];
}
int main()
{
    fscanf(f,"%d",&N);
    V[1][0]=V[1][1]=1;
    V[2][0]=1;V[2][1]=2;
    if(N<=2)
    {
        fprintf(g,"%d",(N==1 ? 1:2));
    }
    else
    {
        int i=3;
        while(i<=N)
        {
            copiere();
            add();
            i++;
        }
        n=V[2][0];
        for(int i=n;i>0;i--)
        {
            CB=BASE/10;
            while(CB>10&&CB>V[2][i]&&i!=n)
            {
                CB/=10;
                fputc('0',g);
            }
            fprintf(g,"%d",V[2][i]);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
