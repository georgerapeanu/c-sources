#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("queue.in","r");
FILE *g=fopen("queue.out","w");
stack <long long> s1,s2;
char v[200];
int n,i,nr;
char c1,c2;
int main()
{
    fscanf(f,"%d\n",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%c%c",&c1,&c2);
        if(c2=='u')
        {
            fscanf(f,"sh_back(%d)\n",&nr);
            s1.push(nr);
            fprintf(g,"%d: read(%d) push(1,%d)\n",i,nr,nr);
        }
        else
        {
            fscanf(f,"p_front()\n");
            fprintf(g,"%d: ",i);
            if(!s2.empty())
            {
                fprintf(g,"pop(2) write(%d)\n",s2.top());
                s2.pop();
            }
            else
            {
                while(s1.size()!=1)
                {
                    int tmp=s1.top();
                    fprintf(g,"pop(1) push(2,%d) ",tmp);
                    s2.push(s1.top());
                    s1.pop();
                }
                nr=s1.top();
                s1.pop();
                fprintf(g,"pop(1) write(%d)\n",nr);
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
