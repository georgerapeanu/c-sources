#include <cstdio>
using namespace std;
int n,m,i,j,v[50001],s[50001][4];
int maxi(int a,int b)
{
    if(a>b)
    return a;
    return b;
}
int main()
{
    FILE *f;
    f=fopen("tren1.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {fscanf(f,"%d",&v[i]);v[i]+=v[i-1];}
    fscanf(f,"%d",&m);
    fclose(f);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=3;j++)
        {
                if(i<m)
                {
                    s[i][j]=maxi(s[i-1][j],s[0][j-1]+v[i]);
                }
                else
                s[i][j]=maxi(s[i-1][j],s[i-m][j-1]+v[i]-v[i-m]);
        }
    }
    f=fopen("tren1.out","w");
    fprintf(f,"%d\n",s[n][3]);
    fclose(f);
    return 0;
}
