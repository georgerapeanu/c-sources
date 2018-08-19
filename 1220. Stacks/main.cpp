#include <cstdio>
#define dig(c) ('0'<=c && c<='9')
#define alpha(c) ('A'<=c&&c<='Z')
using namespace std;
int nr;
char C,c;
int N;
int getint()
{
    int rez=0;
    while(dig(C))
        rez=rez*10+C-'0',C=fgetc(stdin);
    return rez;
}
struct stiva
{
    int nr;
    stiva *pre;
    stiva(int val)
    {
        nr=val;
        pre=NULL;
    }
};
stiva *S[1001];
void push(int a,int b)
{
    stiva *nod=new stiva(b);
    nod->pre=S[a];
    S[a]=nod;
}
int pop(int a)
{
   int val=S[a]->nr;
   stiva *nod=S[a]->pre;
   delete S[a];
   S[a]=nod;
   return val;
}
int main()
{
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        do
        {
            C=getc(stdin);
            if(C=='U')
                c='U';
            else if(C=='O')
                c='O';
        }
        while(alpha(C));
        if(c=='U')
        {
            C=getc(stdin);
            int a=getint();C=fgetc(stdin);int b=getint();
            push(a,b);
        }
        else
        {
            C=getc(stdin);
            int a=getint();
            printf("%d\n",pop(a));
        }
        C=getc(stdin);
    }
    return 0;
}
