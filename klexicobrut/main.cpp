#include <cstdio>
using namespace std;
FILE *f=fopen("klexico.in","r");
FILE *g=fopen("klexico.out","w");
char B[150],A[150];
int N,K,rez;
int cmp(int i)
{
    int j=i;
    while(B[j]==A[j]&&j<=i+K-1)
        j++;
    if(j==i+K)
        return 0;
    if(B[j]>A[j])
        return 1;
    if(B[j]<A[j])
        return -1;
    return 0;
}
int backtr(int pas)
{
    if(pas>N)
    {
        rez++;
        fputs(B+1,g);
        fprintf(g,"\n");
        rez%=666013;
    }
    else
    {
        for(char c='a';c<='z';c++)
        {
            B[pas]=c;
            if(pas<K||cmp(pas-K+1)==1)
                backtr(pas+1);
            B[pas]='\0';
        }
    }
}
int main()
{
    fscanf(f,"%d %d\n",&N,&K);
    fgets(A+1,150,f);
    backtr(1);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
