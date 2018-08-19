#include <cstdio>
using namespace std;
FILE *f=fopen("domino2.in","r");
FILE *g=fopen("domino2.out","w");
void rez(int n)
{
    if(n==1)
    {fprintf(g,"1 1\n");return ;}
    rez(n-2);
    fprintf(g,"1 %d\n",n);
    for(int i=2;i<n-1;i+=2)
    {
        fprintf(g,"%d %d\n%d %d\n%d %d\n%d %d\n",n,i,i,n-1,n-1,i+1,i+1,n);
    }
    fprintf(g,"%d %d\n",n,n);
    fprintf(g,"%d %d\n",n,n-1);
    fprintf(g,"%d %d\n",n-1,n-1);
    fprintf(g,"%d %d\n",n-1,1);
}
int main()
{
    int N;
    fscanf(f,"%d",&N);
    if(N==2){fprintf(g,"1 1\n1 2\n2 2");return 0;}
    if(N%2==0){fprintf(g,"-1");return 0;}
    rez(N);
    fclose(f);
    fclose(g);
    return 0;
}
