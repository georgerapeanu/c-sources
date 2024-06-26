#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
FILE *f=fopen("taste.in","r");
FILE *g=fopen("taste.out","w");
typedef struct{int x,y;} date;
date val[10];
int rez;
int minim=999999,i,j,numar;
char c;
int calorii(int x,int y)
{
    return abs(val[x].x-val[y].x)+abs(val[x].y-val[y].y);
}
int main()
{
    for(i=0;i<10;i++)
        fscanf(f,"%d %d\n",&val[i].x,&val[i].y);
    fscanf(f,"%d",&numar);
    for(i=numar/100;i<100;i+=24)
    {
        for(j=numar%100;j<100;j+=60)
        {
            if(minim>calorii(i/10,i%10)+calorii(i%10,j/10)+calorii(j/10,j%10))
            {
                rez=i*100+j;
                minim=calorii(i/10,i%10)+calorii(i%10,j/10)+calorii(j/10,j%10);
            }
        }
    }
    if(rez)
    fprintf(g,"%d\n%d",minim,rez);
    else
        fprintf(g,"0\n0000");
    fclose(f);
    fclose(g);
    return 0;
}
