#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("1expr.in","r");
FILE *g=fopen("1expr.out","w");
int minim[6562][4],i,T,N,j,k,rez[4],p[4],p2[4];
char E[6562][13123];
int bst(int j,int k)
{
    int l=0;
    for(int i=0;i<4;i++)
        if(minim[j][i]+2*(i<k)<minim[j][l]+2*(l<k))
            l=i;
    return l;
}
void adunare()
{
    int x1,x2;
    x1=bst(j,0);
    x2=bst(i-j,0);
    if(minim[rez[0]][p[0]]+minim[i-rez[0]][p2[0]]+2*((p[0]<0)+(p2[0]<0))+1>minim[j][x1]+minim[i-j][x2]+2*((x1<0)+(x2<0))+1)
    {
        rez[0]=j;
        p[0]=x1;
        p2[0]=x2;
    }
}
void inmultire()
{
    int x1,x2;
    x1=bst(j,1);
    x2=bst(i/j,1);
    if(minim[rez[1]][p[1]]+minim[i/rez[1]][p2[1]]+2*((p[1]<1)+(p2[1]<1))+1>minim[j][x1]+minim[i/j][x2]+2*((x1<1)+(x2<1))+1)
    {
        rez[1]=j;
        p[1]=x1;
        p2[1]=x2;
    }
}

int main()
{
    minim[1][0]=minim[1][1]=minim[1][2]=minim[1][3]=1;
    E[1][0]=E[1][1]=E[1][2]=E[1][3]='1';
    for(i=2;i<=6561;i++)
    {
        rez[0]=rez[1]=rez[2]=rez[3]=p[0]=p[1]=p[2]=p[3]=p2[0]=p2[1]=p2[2]=p2[3]=0;
        for(j=1;j<i;j++)
        {
            adunare();
            if(j!=1){
                if(i%j==0)
                    inmultire();
                putere();
            }
        }
    }
    return 0;
}
