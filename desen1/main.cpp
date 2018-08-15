#include <cstdio>
using namespace std;
FILE *f=fopen("desen1.in","r");
FILE *g=fopen("desen1.out","w");
int N,M,A[1010][1010],i,j;
bool B[1010][1010];
char c[1010][1010];
int stare(int i, int j)
{
	int c=0;
	if (B[i-1][j]+B[i-1][j-1]==1) c++;
	if (B[i-1][j]+B[i-2][j]==1) c++;
	if (B[i-1][j]+B[i-1][j+1]==1) c++;
	return c;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            fscanf(f,"%d",&A[i][j]);
    for(i=2;i<N;i++)
    {
        for(j=2;j<M;j++)
        {
            if(stare(i,j)==A[i-1][j])
                B[i][j]=B[i-1][j];
            else
                B[i][j]=B[i-1][j]^1;
        }
    }
    for(i=1;i<=N;i++)
    {
        fprintf(g,".");
        for(j=2;j<=M;j++)
        {
          if (B[i][j-1]!=B[i][j]) fprintf(g,"|");
		  else fprintf(g,".");
		  if (B[i+1][j]!=B[i][j]) fprintf(g,"_");
		  else fprintf(g,".");
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
