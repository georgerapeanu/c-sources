#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("rama.in","r");
FILE *g=fopen("rama.out","w");
int M,N;
int S[701][701];
int E[701][701];
char V[701][705];
int arie=0;
int col[705];
int len=0;
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(int i=1;i<=N;i++,fgetc(f))
        for(int j=1;j<=M;j++)
        {
            V[i][j]=fgetc(f);
            S[i][j]=S[i-1][j]+(V[i][j]=='1');
            E[i][j]=E[i][j-1]+(V[i][j]=='1');
        }
    for(int i=1;i<=N;i++)
    {
        if((N-i+1)*M<=arie) break;
        for(int j=N;j>=i;j--)
        {
            if((j-i+1)*M<=arie) break;
            len=0;
            int st=1;
            for(int k=1;k<=M;k++)
            {
                if(S[j][k]-S[i-1][k]==j-i+1)
                {
                    col[++len]=k;
                    while(E[j][k]-E[j][col[st]-1]<k-col[st]+1||E[i][k]-E[i][col[st]-1]<k-col[st]+1)
                        st++;
                    arie=max(arie,(j-i+1)*(k-col[st]+1));
                }
            }
        }
    }
    fprintf(g,"%d\n",arie);
    fclose(f);
    fclose(g);
    return 0;
}
