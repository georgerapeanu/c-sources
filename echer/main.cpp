#include <cstdio>
using namespace std;
FILE *f,*g;
short cer;
int l1,l2;
long m,n,x,y,ma,mi,k,i,nrafis=0;
int main()
{
    f=fopen("echer.in","r");
    fscanf(f,"%hd %d %d %ld %ld",&cer,&l1,&l2,&m,&n);
    fclose(f);
    x=m/l1;
    y=n/l2;
    ma=x>y ? x:y;
    mi=x<y ? x:y;
    if(x==y)
    k=3*x-2;
    else if(ma-mi==1)
    k=3*mi-1;
    else if((ma-mi)%2==0)
    k=3*mi-2+2*(ma-mi);
    else
    k=3*mi-3+2*(ma-mi);
    g=fopen("echer.out","w");
    if(cer==1)
    {
        fprintf(g,"%ld",k);
    }
    else
    {
        fprintf(g,"1 ");
        for(i=1;i<mi;i++)
        fprintf(g,"2 3 1 ");
        if(x-y==1) fprintf(g,"4 ");
        else if(y-x==1) fprintf(g,"2 ");
        nrafis=(mi-1)*3+2;
        i=1;
        if(x-y>1)
        {
            while(nrafis<=k)
            {
                if(i%4==1)
                fprintf(g,"4 ");
                else if(i%4==2)
                fprintf(g,"6 ");
                else if(i%4==3)
                fprintf(g,"3 ");
                else
                fprintf(g,"1 ");
                i++;
                nrafis++;
            }
        }
        else if(y-x>1)
        {
                while(nrafis<=k)
            {
                if(i%4==1)
                fprintf(g,"2 ");
                else if(i%4==2)
                fprintf(g,"7 ");
                else if(i%4==3)
                fprintf(g,"5 ");
                else
                fprintf(g,"1 ");
                nrafis++;
                i++;
            }
        }

    }
    return 0;
}
