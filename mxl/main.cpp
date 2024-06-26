#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
FILE *f=fopen("mxl.in","r");
FILE *g=fopen("mxl.out","w");
int N,K,i,j,x,y,suma;
long long M[50][50];
char c[50][50][260];
long long eval(long long x,long long y)
{
        long long n=strlen(c[x][y]),i=0,suma=0,nr=0,b=0;
        while(i<n)
        {
            nr=0;
            while('0'<=c[x][y][i]&&c[x][y][i]<='9')
            {
                nr=nr*10+c[x][y][i]-'0';
                i++;
            }
            if(c[x][y][i]==':')
            {
                b=0;
                i++;
                while('0'<=c[x][y][i]&&c[x][y][i]<='9')
                {
                    b=b*10+c[x][y][i]-'0';
                    i++;
                }
                if(!M[nr][b])
                suma=suma+eval(nr,b);
                else
                    suma=suma+M[nr][b];
            }
            else
            {
                suma+=nr;
            }
            i++;
        }
        M[x][y]=suma;
        return suma;
}
int main()
{
    fscanf(f,"%d %d\n",&N,&K);
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d %d ",&x,&y);
        fgets(c[x][y],260,f);
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            if(c[i][j]!='\0'&&!M[i][j])
                eval(i,j);
                fprintf(g,"%lld ",M[i][j]);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
