#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
short v[51][51],n,i,j,a,b,st,fn,contor;
char c[101],d[101];
int main()
{
    FILE *f;
    f=fopen("rv.in","r");
    fscanf(f,"%s",&c);
    fclose(f);
    n=ceil(double(strlen(c))/2);
    fn=strlen(c)-1;
    for(i=1;i<n;i++)
    {v[0][i]=-1;v[i][0]=1;}
    v[0][0]=0;
    if(strlen(c)%2==0)
    {
        a=strlen(c)/2-1;
        b=strlen(c)/2;
    }
    else
    {
        a=b=strlen(c)/2;
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(c[a-i+1]>c[b+j-1])
            {
                v[i][j]=1;
            }
            else if(c[a-i+1]<c[b+j-1])
            {
                v[i][j]=-1;
            }
            else
            {
                v[i][j]=v[i-1][j-1];
            }
        }
    }
    i=j=n;
    while(st<=fn)
    {
        if(contor%2==0)
        {
            if(v[i][j]==1||v[i][j]==0)
            {
                d[contor]=c[st];
                st++;
                contor++;
                i--;
            }
            else
            {
                d[contor]=c[fn];
                fn--;
                contor++;
                j--;
            }
        }
        else
        {
            if(v[i][j]==1||v[i][j]==0)
            {
                d[contor]=c[fn];
                fn--;
                contor++;
                j--;
            }
            else
            {
                i--;
                d[contor]=c[st];
                st++;
                contor++;
            }
        }

    }
    f=fopen("rv.out","w");
    fprintf(f,"%s",d);
    fclose(f);
    return 0;
}
