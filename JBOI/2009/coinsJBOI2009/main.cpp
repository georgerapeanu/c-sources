#include <cstdio>
using namespace std;
int V[4][9];
char sgn[4];
int coin,sign;
bool eval(int coin,int sign)
{
    int mask=(1<<12)-1,mask1,mask2,mask3;
    for(int i=1;i<=3;i++)
    {
        mask1=0;
        mask2=0;
        for(int j=1;j<=4;j++)mask1|=(1<<(V[i][j]-1));
        for(int j=5;j<=8;j++)mask2|=(1<<(V[i][j]-1));
        mask3=(((1<<12)-1)^(mask1|mask2));
        if(sgn[i]=='<')
        {
            mask&=(mask^mask3);
            if(sign==0) mask&=(mask^mask2);
            else mask&=(mask^mask1);
        }
        else if(sgn[i]=='=')
        {
            mask&=(mask^mask1);
            mask&=(mask^mask2);
        }
        else
        {
            mask&=(mask^mask3);
            if(sign==0) mask&=(mask^mask1);
            else mask&=(mask^mask2);
        }
    }
    return (mask&(1<<(coin-1)))!=0;
}
int main()
{
    for(int i=1;i<4;i++)
    {
        scanf("%d %d %d %d %c %d %d %d %d",&V[i][1],&V[i][2],&V[i][3],&V[i][4],&sgn[i],&V[i][5],&V[i][6],&V[i][7],&V[i][8]);
    }
    for(int i=1;i<=12;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(eval(i,j))
            {
                if(!coin){coin=i;sign=j;}
                else{printf("indefinite\n");return 0;}
            }
        }
    }
    if(!coin)printf("impossible\n");
    else printf("%d%c",coin,(sign==0 ? '-':'+'));
    return 0;
}
