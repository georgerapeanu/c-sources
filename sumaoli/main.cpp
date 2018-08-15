#include <cstdio>
using namespace std;
FILE *f=fopen("suma.in","r");
FILE *g=fopen("suma.out","w");
int suma,impart=1,N,a,b,c,i,pb,pc,cb,cc,suma1,impart1,p10c,num,r,da,db;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        p10c=pb=pc=1;
        fscanf(f,"%d %d %d",&a,&b,&c);
        cb=b;
        cc=c;
        while(cb)
        {
            pb*=10;
            cb/=10;
        }
        if(b==0)
            pb=10;
        while(cc)
        {
            p10c*=10;
            pc+=p10c;
            cc/=10;
        }
        if(c==0)
            p10c=10;
        else
            pc/=10;
        impart1=9*pc*pb;
        suma1=a*pb*p10c+p10c*b+c-b-pb*a;
        ///gcd(impart1,impart)
        da=impart1;
        db=impart;
        r=da%db;
        while(r)
        {
            da=db;
            db=r;
            r=da%db;
        }
        num=db;
        ///
        num=impart*impart1/num;
        suma=suma*(num/impart);
        impart=num;
        suma1=suma1*(num/impart1);
        suma+=suma1;
    }
    a=suma/impart;
    suma=suma-a*impart;
    ///gcd(suma,impart)
    da=suma;
    db=impart;
        r=da%db;
        while(r)
        {
            da=db;
            db=r;
            r=da%db;
        }
        num=db;
        ///
    b=suma/num;
    c=impart/num;
    fprintf(g,"%d %d %d",a,b,c);
    fclose(f);
    fclose(g);
    return 0;
}
