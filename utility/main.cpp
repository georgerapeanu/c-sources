#include <cstdio>
using namespace std;
FILE *f,*g;
char s[10],c,ch;
int i;
int main()
{
//    f=fopen("utility.in","r");
//    g=fopen("utility.out","w");
//    for(i=32;i<=127;i++)
//    {
//        fscanf(f,"%s",&s);
//        fprintf(g,"strcpy(c[%d],%c%s%c);\n",i,c,s,c);
//    }
//    fclose(f);
//    fclose(g);
    f=fopen("criptat.out","r");
    g=fopen("criptat.in","r");
    while(c==ch)
    {
        fscanf(f,"%c",&c);
        fscanf(g,"%c",&ch);
        i++;
    }
    if(c<ch)
    printf("-1");
    else
    printf("1");
    return 0;
}
