#include <cstdio>
using namespace std;
FILE *f=fopen("aparitii.in","r");
FILE *g=fopen("aparitii.out","w");
int frecv[10][10];
int N,K,i,j,val;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        j=9;
        while(val)
        {
            frecv[j][val%10]++;
            val/=10;
            j--;
        }
    }
    val=0;
    for(i=0;i<=9;i++)
    {
       for(j=0;j<=9;j++)
       {
           if(frecv[i][j]%K!=0)
           {
               val=val*10+j;
           }
       }
    }
    fprintf(g,"%d",val);
    fclose(f);
    fclose(g);
    return 0;
}
