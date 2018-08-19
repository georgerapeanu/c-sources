#include <deque>
#include <cstdio>
using namespace std;
FILE *f=fopen("maxim.in","r");
FILE *g=fopen("maxim.out","w");
int a,b,c,cf;
deque<int> D;
int i,N,j;
char C[10];
int main()
{
    fscanf(f,"%d %d %d",&a,&b,&c);
    for(i=a;i<=b;i++)
    {
        sprintf(C,"%d\0",i);
        j=0;
        while(C[j]!='\0')
        {
            cf=C[j]-'0';
            while(c>0&&!D.empty()&&D.back()<cf)
            {
                c--;
                D.pop_back();
            }
            D.push_back(cf);
            j++;
        }
    }
    while(c--)
        D.pop_back();
    while(!D.empty())
    {
        fprintf(g,"%d",D.front());
        D.pop_front();
    }
    fclose(f);
    fclose(g);
    return 0;
}
