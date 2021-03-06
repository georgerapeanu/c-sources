#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("joc9.in","r");
FILE *g=fopen("joc9.out","w");
int X[200][200],N,i,A[200],B[200],C[200],j;
pair <int,int> V[3];
int cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.first!=b.first)
        return a.first>b.first;
    return a.second<b.second;
}
int main()
{
    fscanf(f,"%d",&N);
    N++;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=i;j++)
            fscanf(f,"%d",&X[i][j]);
    }
    for(i=1;i<=N;i++)
    {
        A[i]=X[N][i];
        B[i]=X[i][i];
        C[i]=X[i][1];
    }
    for(i=N-1;i>0;i--)
    {
        for(j=1;j<=i;j++)
        {
            A[j]=max(A[j],A[j+1])+X[i][j];
            B[j]=max(B[j+1],B[j])+X[j+N-i][j];
            C[j]=max(C[j],C[j+1])+X[N+j-i][N-i+1];
        }
    }
    V[0]=make_pair(A[1],X[1][1]);
    V[1]=make_pair(B[1],X[N][1]);
    V[2]=make_pair(C[1],X[N][N]);
    sort(V,V+3,cmp);
    fprintf(g,"%d\n%d",V[0].first,V[0].second);
    fclose(f);
    fclose(g);
    return 0;
}
