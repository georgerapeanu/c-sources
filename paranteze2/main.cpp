#include <cstdio>
#include <cstring>
using namespace std;
long long desch,inch,i,nr;
char s[100000];
int main()
{
    FILE *f, *g;
    f=fopen("paranteze2.in","r");
    fscanf(f,"%s",s);
    fclose(f);
    for(i=0;i<strlen(s)/2;i++)
    {
        if(s[i]=='(')
           desch++;
        else
        inch++;
        if(s[strlen(s)-i]=='(')
           desch++;
           else
           inch++;
    }
    if(desch>inch)
    nr=(desch-inch)/2;
    else
    nr=(inch-desch)/2;
    g=fopen("paranteze2.out","w");
    fprintf(g,"%lld",nr);
    fclose(g);
    return 0;
}
