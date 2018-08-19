#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("sumacfnr.in","r");
FILE *g=fopen("sumacfnr.out","w");
int nr;
char c;
int rez;
int suma()
{
    c=fgetc(f);
    if(c!='\n')
        {
            rez+=c-'0';
            suma();
        }
    else
        return rez;
}
int main()
{
    fprintf(g,"%d",suma());
    fclose(f);
    fclose(g);
    return 0;
}
