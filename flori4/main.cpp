#include <cstdio>
using namespace std;
FILE *f=fopen("flori4.in","r");
FILE *g=fopen("flori4.out","w");
int x=2,y=3,tmp,i,N;
int main()
{
    fscanf(f,"%d",&N);
    if(N==1)
        fprintf(g,"1");
    else if(N==2)
        fprintf(g,"2");
    else
    {
        i=2;
        while(i<N)
        {
            tmp=y;
            y=(x+y)%9001;
            x=tmp;
            i++;
        }
        y--;
        if(y<0)
            y=9000;
        y%=9001;
        fprintf(g,"%d",y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
