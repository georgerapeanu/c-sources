#include <cstdio>
using namespace std;
FILE *f=fopen("cardinal.in","r");
FILE *g=fopen("cardinal.out","w");
int N,P;
long long  i,j;
int i1,i2,A,S,k;
long long nr,z;
bool E[100002];
int  nx[2],nrprim[10001];
int  x[2][10001];///numarul in sine(k1*k2*k3*...)^(p+1)
int  y[2][10001];///pozitia de unde iei numarul
int main()
{
    fscanf(f,"%d %d",&N,&P);
    for(i=2;i*i<=N;i++)
    {
        if(E[i]==0)
        {
            nr=1;z=i;
            for(j=P+1;j!=0;j>>=1)
            {
                if(j&1) {nr*=z;if(nr>N)nr=N+1;}
                z*=z;
                if(j!=1&&z>N)
                {z=N+1;nr=N+1;}
            }
            if(nr>N)
                break;
            A+=N/nr;
            nx[1]++;
            nrprim[nx[1]]=nr;
            x[1][nx[1]]=nr;
            y[1][nx[1]]=nx[1];
            for(j=i*i;j*j<=N;j+=i)
            {
                E[j]=1;
                if(i==2&&nx[1]!=1)
                {
                    z=1;
                }
            }
        }
    }
    i1=1;
    i2=0;
    nr=nx[1];
    S=1;///semn
    while(nx[i1]!=0)
    {
        nx[i2]=0;S=-S;
        for(j=1;j<=nx[i1];j++)///pentru toate numerele din categorie din acest moment(ca nr de div)
        {
            for(k=y[i1][j]+1;k<=nr;k++)
            {
                if((long long)(x[i1][j])*((long long)(nrprim[k]))<=N)///testam daca le putem inmulti cu un nr prim cu care nu o fost luati deja
                {                                                    ///ex:2 3 7 5 va fi gasit si in 2 3 5 7,deci ii ok sa generam crescator
                    nx[i2]++;
                    x[i2][nx[i2]]=x[i1][j]*nrprim[k];
                    y[i2][nx[i2]]=k;
                    A+=(N/(x[i1][j]*nrprim[k]))*S;///nr var proaste;
                }
                else
                    break;
            }
        }
        i1=i2;
        i2=1-i2;
    }
    fprintf(g,"%d",N-A-1);
    fclose(f);
    fclose(g);
    return 0;
}
