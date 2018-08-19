#include <cstdio>
using namespace std;
FILE *f,*g;
int m[2][200];
int c,n,i,nr,st=10002,sf,ram;
int main()
{
    f=fopen("panglica.in","r");
    fscanf(f,"%d %d",&n,&c);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&nr);
        if(m[0][nr-1]==0)
        m[0][nr-1]=i;
        m[1][nr-1]=i;
    }
    fclose(f);
    for(i=0;i<c;i++)
    {
        if(m[0][i]-1+(n-m[1][i])<st-1+(n-sf))
        {
            st=m[0][i];
            sf=m[1][i];
            nr=i+1;
        }
    }
    st=st-1;
    sf=n-sf;
    ram=n-st-sf;
    g=fopen("panglica.out","w");
    fprintf(g,"%d\n%d\n%d\n%d",ram,nr,st,sf);
    fclose(g);
    return 0;
}
