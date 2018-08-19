#include <cstdio>
#include <algorithm>
#define t first
#define ind second
using namespace std;
FILE *f=fopen("wall.in","r");
FILE *g=fopen("wall.out","w");
pair<int,int> V[100005];
int N,Z;
int ppaz=1;
int main()
{
    fscanf(f,"%d %d",&N,&Z);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i].t);
        V[i].ind=i;
    }
    sort(V+1,V+1+N);
    int i=N;
    while(i&&V[i].t>=Z)
        ppaz=Z,i--;
    fprintf(g,"%d\n",i);
    for(int j=N;j>i;j--)
        fprintf(g,"%d %d\n",V[j].ind,Z);
    for(;i;i--)
    {
        if(Z-ppaz>=V[i].t)
        {fprintf(g,"%d %d\n",V[i].ind,Z);ppaz+=V[i].t;}
        else
        {fprintf(g,"%d %d\n",V[i].ind,1);ppaz-=V[i].t;}
    }
    fclose(f);
    fclose(g);
    return 0;
}
