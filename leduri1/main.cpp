#include <cstdio>
#include <cstring>
using namespace std;
char c[4][9],a;
short ora[4],nr,i,j,ora1[8],v[]={1,2,4,8},suma;
long t;
void conditii()
{
    switch(ora1[i])
    {
        case 0:c[0][i]=c[1][i]=c[2][i]=c[3][i]='x';
        break;
        case 1:c[0][i]=c[1][i]=c[2][i]='x';c[3][i]='o';
        break;
        case 2:c[0][i]=c[1][i]=c[3][i]='x';c[2][i]='o';
        break;
        case 3:c[0][i]=c[1][i]='x';c[2][i]=c[3][i]='o';
        break;
        case 4:c[0][i]=c[2][i]=c[3][i]='x';c[1][i]='o';
        break;
        case 5:c[0][i]=c[2][i]='x';c[1][i]=c[3][i]='o';
        break;
        case 6:c[0][i]=c[3][i]='x';c[1][i]=c[2][i]='o';
        break;
        case 7:c[0][i]='x';c[1][i]=c[2][i]=c[3][i]='o';
        break;
        case 8:c[0][i]='o';c[1][i]=c[2][i]=c[3][i]='x';
        break;
        case 9:c[0][i]=c[3][i]='o';c[1][i]=c[2][i]='x';
        break;
    }
}
int main()
{
    FILE *f;
    f=fopen("leduri1.in","r");
    for(i=0;i<=3;i++)
    {
        for(j=0;j<=7;j++)
        {
            fscanf(f,"%c",&c[i][j]);
        }
        fscanf(f,"%c",&a);
    }
    fscanf(f,"%ld",&t);
    fclose(f);
    for(i=0;i<8;i++)
    {
        suma=0;
        for(j=0;j<4;j++)
        {
            if(c[j][i]=='o')
            {
               suma+=v[3-j];
            }
        }
        ora[i/2]*=10;
        ora[i/2]+=suma;
    }
        ora[3]+=t%100;
        t=t/100;
        t+=ora[3]/100;
        ora[3]%=100;
        ora[2]+=t%60;
        t=t/60;
        t+=ora[2]/60;
        ora[2]%=60;
        ora[1]+=t%60;
        t=t/60;
        t+=ora[1]/60;
        ora[1]%=60;
        ora[0]+=t;
        ora[0]%=24;
        ora1[0]=ora[0]/10;
        ora1[1]=ora[0]%10;
        ora1[2]=ora[1]/10;
        ora1[3]=ora[1]%10;
        ora1[4]=ora[2]/10;
        ora1[5]=ora[2]%10;
        ora1[6]=ora[3]/10;
        ora1[7]=ora[3]%10;
        for(i=0;i<8;i++)
        {
            conditii();
            switch(i)
            {
                case 0:c[0][i]=c[1][i]=' ';
                break;
                case 2:
                case 4:c[0][i]=' ';
                break;
            }
        }
     f=fopen("leduri1.out","w");
    for(i=0;i<4;i++)
    fprintf(f,"%s\n",c[i]);
    fclose(f);
    return 0;
}
