#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("rgb.in","r");
FILE *g=fopen("rgb.out","w");
int T,m,M;
int R,G,B,cR,cG,cB;
int C[4][105];
int ord[4];
int ind;
int add(int a,int b)
{
    C[a][++C[a][0]]=b;
}
void init()
{
    for(int i=1;i<4;i++)C[i][0]=0;
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d %d %d",&R,&G,&B);
        init();
        cR=1;cG=2;cB=3;
        if(B<R){swap(B,R);swap(cB,cR);}
        if(B<G){swap(G,B);swap(cG,cB);}
        if(G<R){swap(G,R);swap(cG,cR);}
        int off=100;
        int eG=G-R,eB=B-R;
        if(B>2*R){fprintf(g,"-1\n");continue;}
        for(int i=1;i<=R;i++)
        {
            if(eG){add(cG,i*off);eG--;}
            if(eB){add(cB,1+i*off);eB--;}
            add(cR,i*off+2);
            add(cG,i*off+3);
            add(cB,i*off+4);
        }
        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<=C[i][0];j++)fprintf(g,"%d ",C[i][j]);
            fprintf(g,"\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
