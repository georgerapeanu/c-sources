#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
typedef pair<long long,long long> point;
FILE *f,*g;
point prim,secund,med;
long long dr,st,n,k,x,y,i,cdr,cst;
int main()
{
    f=fopen("z.in","r");
    g=fopen("z.out","w");
    fscanf(f,"%lld %lld",&n,&k);
    for(i=1;i<=k;i++)
    {
        fscanf(f,"%lld %lld",&x,&y);
        st=1;
        dr=pow(2,n);
        prim.first=1;
        prim.second=1;
        secund.first=dr;
        secund.second=dr;
        dr=dr*dr;
        while(prim.first!=secund.first||secund.second!=prim.second)
        {
            med=point((prim.first+secund.first)/2,(prim.second+secund.second)/2);
            if(x<=med.first&&y<=med.second)
            {
                cdr=dr;
                cst=st;
                dr=cdr-(cdr-cst+1)/4*3;
                secund.first=(prim.first+secund.first)/2;
                secund.second=(prim.second+secund.second)/2;
            }
            else if(x<=med.first&&y>med.second)
            {
                cdr=dr;
                cst=st;
                dr=cdr-(cdr-cst+1)/2;
                st=cdr-(cdr-cst+1)/4*3+1;
                prim.second=(prim.second+secund.second)/2+1;
                secund.first=(prim.first+secund.first)/2;
            }
            else if(x>med.first&&y<=med.second)
            {
                cdr=dr;
                cst=st;
                st=cdr-(cdr-cst+1)/2+1;
                dr=(cdr-cst+1)/4*3+cst-1;
                prim.first=(prim.first+secund.first)/2+1;
                secund.second=(prim.second+secund.second)/2;
            }
            else
            {
                cdr=dr;
                cst=st;
                st=(cdr-cst+1)/4*3+cst;
                prim.first=(prim.first+secund.first)/2+1;
                prim.second=(prim.second+secund.second)/2+1;
            }
        }
        fprintf(g,"%lld\n",st);
    }
    fclose(f);
    fclose(g);
    return 0;
}
