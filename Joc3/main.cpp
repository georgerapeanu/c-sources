#include <cstdio>
using namespace std;
FILE *f=fopen("joc3.in","r");
FILE *g=fopen("joc3.out","w");
int N;
int V[100005];
int xo;
int p,q;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        if((N-i)%2==1)xo^=V[i];
    }
    if(xo==0){fprintf(g,"-1");return 0;}
    for(int i=N-1;i>0;i-=2)
    {
        if((xo^V[i])>V[i]&&((xo^V[i])-V[i])<=V[i-1]){p=i-1;q=(xo^V[i])-V[i];}
        else if((xo^V[i])<V[i]){p=i;q=V[i]-(xo^V[i]);}
    }
    fprintf(g,"%d %d",p,q);
    return 0;
}
