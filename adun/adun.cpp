#include <cstdio>
using namespace std;
FILE *f=fopen("adun.in","r");
FILE *g=fopen("adun.out","w");
char C;
int i,e=1,cnt=1;
long long t1=-1,t2=-1,rez=-1;
int main()
{
    while(C!=EOF)
    {
            C=fgetc(f);
            switch(C)
            {
                case '+':
                case '=':cnt++;
                break;
                case ';':
                if(t1==-1)
                    t1=rez-t2;
                else if(t2==-1)
                    t2=rez-t1;
                else if(rez==-1)
                    rez=t1+t2;
                fprintf(g,"%lld+%lld=%lld;\n",t1,t2,rez);
                rez=t1=t2=-1;
                cnt=1;
                break;
                case' ':case '\n':break;
                default:
                if(cnt==1)
                {
                    if(t1==-1)
                        t1=0;
                    t1=t1*10+C-'0';
                }
                else if(cnt==2)
                {
                    if(t2==-1)
                        t2=0;
                    t2=t2*10+C-'0';
                }
                else if(cnt==3)
                {
                    if(rez==-1)
                        rez=0;
                    rez=rez*10+C-'0';
                }
                break;
            }
    }
    fclose(f);
    fclose(g);
    return 0;
}
