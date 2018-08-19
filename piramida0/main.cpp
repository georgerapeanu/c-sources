#include <cstdio>
using namespace std;
short n,l,cl,anterior,v[2700],temp[4],c,j,i,cfmax,pozcfmax[2700],nr,maxim;
FILE *f,*g;
int main()
{
    f=fopen("piramida.in","r");
    fscanf(f,"%hu %hu",&n,&l);
    fclose(f);
    cl=l;
    anterior=l*n;
    do
    {
        c=anterior;
            j=0;
            while(c!=0)
            {
                temp[j++]=c%10;
                c/=10;
            }
            nr=0;
            for(i=j-1;i>=0;i--)
            {
                v[v[0]+j-i]=temp[i];
                nr=nr*10+temp[i];
                v[v[0]+j+j-i]=temp[i];
                temp[i]=0;
                if(temp[i]>cfmax)
                {
                    cfmax=temp[i];
                    pozcfmax[0]=2;
                    pozcfmax[]
                }
            }
            v[0]+=2*j;
            if(nr>maxim)
                maxim=nr;
        l-=2;
        anterior+=l;
    }
    while(l>0);
    g=fopen("piramida.out","w");
    v[v[0]]=v[v[0]-1]=0;
    v[0]-=2;
    for(i=1;i<=v[0];i++)
    fprintf(g,"%hu",v[i]);
    fclose(g);
    return 0;
}
