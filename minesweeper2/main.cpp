#include <cstdio>
using namespace std;
FILE *f=fopen("minesweeper2.in","r");
FILE *g=fopen("minesweeper2.out","w");
int d[300050][4];
int v,N,i,j;
int main()
{
    fscanf(f,"%d",&N);
    fscanf(f,"%d",&v);
    switch(v)
    {
        case 0:d[2][0]=1;break;
        case 1:d[2][1]=d[2][2]=1;break;
        case 2:d[2][3]=1;break;
    }
    for(i=2;i<N;i++)
    {
        fscanf(f,"%d",&v);
        switch(v)
        {
            case 0:d[i+1][0]=d[i][0];break;
            case 1:d[i+1][0]=d[i][2];d[i+1][2]=d[i][1];d[i+1][1]=d[i][0];break;
            case 2:d[i+1][3]=d[i][1];d[i+1][1]=d[i][2];d[i+1][2]=d[i][3];break;
            case 3:d[i+1][3]=d[i][3];break;
            case -1:d[i+1][0]=d[i][0]+d[i][2];d[i+1][1]=d[i][0]+d[i][2];d[i+1][2]=d[i][1]+d[i][3];d[i+1][3]=d[i][1]+d[i][3];break;
        }
    }
    fscanf(f,"%d",&v);
    switch(v)
    {
        case 0:fprintf(g,"%d",d[N][0]);break;
        case 1:fprintf(g,"%d",d[N][1]+d[N][2]);break;
        case 2:fprintf(g,"%d",d[N][3]);break;
        case -1:fprintf(g,"%d",d[N][0]+d[N][1]+d[N][2]+d[N][3]);break;
    }
    fclose(f);
    fclose(g);
    return 0;
}
