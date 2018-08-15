#include <cstdio>
#include <fstream>
#include <algorithm>
#define x first
#define y second
#define NMAX 205
#define inf 1<<30
using namespace std;
FILE *f=fopen("wanted.in","r");
FILE *g=fopen("wanted.out","w");
int a[NMAX][NMAX];///cost minim pt intervalul i,j daca ne aflam in i
int b[NMAX][NMAX];///cost minim pt intervalul i,j daca ne aflam in j
int N;
pair<int,int> V[NMAX];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++) fscanf(f,"%d%d",&V[i].x,&V[i].y);
    sort(V+1,V+1+N);
    for(int i=1;i<=N+1;i++)
    {
        a[i][i]=b[i][i]=V[i].y;
        for(int j=1;j<i;j++)
            a[i][j]=b[i][j]=-inf;
    }
    for(int i=N;i>0;i--)
    {
        for(int j=i+1;j<=N;j++)
        {
            a[i][j]=inf;
            for(int k=i;k<=j;k++)
            {
               int st,dr;
               st=b[i][k-1]+2*V[k].y+V[k].x-V[k-1].x+V[k].x-V[i].x;
               dr=a[k+1][j]+2*V[k].y+V[k+1].x-V[k].x+V[k].x-V[i].x;
               a[i][j]=min(a[i][j],max(st,dr));
            }
            b[i][j]=inf;
            for(int k=i;k<=j;k++)
            {
                int st,dr;
                st=b[i][k-1]+2*V[k].y+V[k].x-V[k-1].x+V[j].x-V[k].x;
                dr=a[k+1][j]+2*V[k].y+V[k+1].x-V[k].x+V[j].x-V[k].x;
                b[i][j]=min(b[i][j],max(st,dr));
            }
        }
    }
    int rez=inf;
    for(int i=1;i<=N;i++)
        rez=min(rez,2*V[i].y+abs(V[i].x)+max(b[1][i-1]+V[i].x-V[i-1].x,a[i+1][N]+V[i+1].x-V[i].x));
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
