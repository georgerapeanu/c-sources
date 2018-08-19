#include <cstdio>
using namespace std;
FILE *f=fopen("expr.in","r");
FILE *g=fopen("expr.out","w");
char c;
int expr();
int fact()
{
    int fa;
    switch(c)
    {
        case '+':c=fgetc(f);fa=fact();break;
        case '-':c=fgetc(f);fa=-fact();break;
        case '(':c=fgetc(f);fa=expr();c=fgetc(f);break;
        default:fa=0;while('0'<=c&&c<='9'){fa=fa*10+c-'0';c=fgetc(f);}break;
    }
    return fa;
}
int term()
{
    int t;
    char first;
    t=fact();
    while(c=='*'||c=='/')
    {
        first=c;
        c=fgetc(f);
        if(first=='*')
            t*=fact();
        else
            t/=fact();
    }
    return t;
}
int expr()
{
    int e;
    char first;
    e=term();
    while(c=='+'||c=='-')
    {
        first=c;
        c=fgetc(f);
        e+=(first=='+' ? 1:-1)*term();
    }
    return e;
}
int main()
{
    c=fgetc(f);
    fprintf(g,"%d",expr());
    fclose(f);
    fclose(g);
    return 0;
}
