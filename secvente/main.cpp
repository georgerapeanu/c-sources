#include <cstdio>
using namespace std;
FILE *f=fopen("secvente.in","r");
FILE *g=fopen("secvente.out","w");
int frecv[3],N,i,j,a;
int main()
{
    for(i=1;i<=3;i++)
    {
        frecv[0]=frecv[1]=frecv[2]=0;
        fscanf(f,"%d",&N);
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%d",&a);
            frecv[a%3]++;
        }
        frecv[1]%=3;
        frecv[2]%=3;
        if(frecv[1]<=frecv[2])
        {
            frecv[2]-=frecv[1];
            frecv[1]=0;
        }
        else
        {
            frecv[1]-=frecv[2];
            frecv[2]=0;
        }
        fprintf(g,"%d\n",N-frecv[1]-frecv[2]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
