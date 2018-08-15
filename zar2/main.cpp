#include <cstdio>
using namespace std;
FILE *f=fopen("zar2.in","r");
FILE *g=fopen("zar2.out","w");
int poz,N,M,I,i,j,tip,Z;
int ind[2505],x,y,x1,y1,newpoz,nrpoz;
const int dirx[]={0,0,-1,-1,-1,0,1,1,1};
const int diry[]={0,1,1,0,-1,-1,-1,0,1};
int main()
{
    fscanf(f,"%d %d",&N,&M);
    fscanf(f,"%d",&I);
    for(i=1;i<=I;i++)
    {
        fscanf(f,"%d %d %d",&poz,&tip,&nrpoz);
        if(tip==9)
            ind[poz]=nrpoz;
        else
        {
            x=(poz-1)/M+1;x=N-x+1;
            y=(poz-1)%M+1;if((N-x+1)%2==0)y=M-y+1;
            x1=x+dirx[tip]*nrpoz;
            y1=y+diry[tip]*nrpoz;
            if(!(x1<1||x1>N||y1<1|y1>M))
            {
                newpoz=0;
                newpoz+=(N-x1)*M;
                if((N-x1+1)%2==0)
                {
                    newpoz+=M-y1+1;
                }
                else
                    newpoz+=y1;
                ind[poz]=newpoz;
            }
        }
    }
    poz=1;
    fscanf(f,"%d",&Z);
    for(i=1;i<=Z;i++)
    {
        fscanf(f,"%d",&nrpoz);
        poz+=nrpoz;
        if(poz>N*M)
            break;
        if(ind[poz])
            poz=ind[poz];
    }
    if(poz>N*M)
        fprintf(g,"1 %d",i);
    else
        fprintf(g,"2 %d",poz);
    fclose(f);
    fclose(g);
    return 0;
}
