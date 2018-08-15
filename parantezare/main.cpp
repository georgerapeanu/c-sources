#include <cstdio>
#include <cstring>
#include <stack>
#include <map>
using namespace std;
FILE *f=fopen("parantezare.in","r"),*g=fopen("parantezare.out","w");
stack <int> s;
map <int,int> rasp;
char c[100010];
int M,nr,i;
int main()
{
    fgets(c,100010,f);
    int n=strlen(c);
    for(i=0;i<n;i++)
    {
        if(c[i]=='(')
           s.push(i);
        else if(c[i]==')')
        {
                int tmp;
                tmp=s.top();
                rasp[tmp]=i;
                s.pop();
        }
    }
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&nr);
        fprintf(g,"%d ",rasp[nr]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
