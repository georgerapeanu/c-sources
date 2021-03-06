#include <cstdio>
using namespace std;
FILE *f=fopen("submultimi.in","r");
FILE *g=fopen("submultimi.out","w");
int A,K,N,i,nr,j;
int subm;
int det(int nr,int bit)
{
    if(bit<0)
        return nr;
    if((nr&(1<<bit+1))==1)
        return det(nr,bit-1);
    if(nr%(1<<bit+1)==0)
        return det(nr+(1<<bit+1)-1,bit-1);
    return det(nr-1,bit-1);
}
int main()
{
    fscanf(f,"%d %d\n",&N,&K);
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d",&A);
       subm= det(A+1,N+1);
        for(j=N-1;j>=0;j--)
        {
            if((subm&(1<<j))==0)
                fprintf(g,"%d ",N-j);
        }
            fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
