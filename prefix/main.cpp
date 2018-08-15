#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("prefix.in","r");
FILE *g=fopen("prefix.out","w");
//bitset <500001> B;
bool B[500001];
char S[500001];
char P[21][21],c;
int N,i,V[21],M,rez,j;
bool mycmp()
{
    int k=1;
    while(k<=V[j]&&P[j][k]==S[i-V[j]+k])
        k++;
    if(k>V[j])
        return 1;
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d\n",&V[i]);
        fgets(P[i]+1,21,f);
    }
    fscanf(f,"%c\n",&c);
    i=0;
    do
    {
        S[++i]=c;
       fscanf(f,"%c\n",&c);
    }
    while(c!='.');
    B[0]=1;
    M=i;
    for(i=1;i<=M;i++)
    {
        for(j=1;j<=N&&!B[i];j++)
        {
            if(i-V[j]>=0&&B[i-V[j]]&&mycmp())
                {B[i]=1;rez=i;}
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
