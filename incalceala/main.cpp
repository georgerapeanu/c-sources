#include <cstdio>
using namespace std;
FILE *f=fopen("incalceala.in","r");
FILE *g=fopen("incalceala.out","w");
char c[20005];
int N,i;
bool rasp;
int poz;
void ok()
{
    if(c[poz]=='(')
    {
      poz++;
      ok();
      if(rasp)
      {
        if(c[poz]==')')
        {
            poz++;
            ok();
        }
        else
            rasp=0;
      }
    }
    else if(c[poz]==')')
    {
        ;
    }
    else
    {
        if(c[poz]=='\0'||c[poz]=='\n')
            return ;
        poz++;
        ok();
    }
}
int corect()
{
    rasp=1;
    poz=0;
    ok();
    return rasp&&(c[poz]=='\n'||c[poz]=='\0');
}
int main()
{
    for(i=1;i<=5;i++)
    {
        fgets(c,20005,f);
        fprintf(g,"%d\n",corect());
    }
    fclose(f);
    fclose(g);
    return 0;
}
