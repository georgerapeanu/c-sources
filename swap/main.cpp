#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("swap.in","r");
FILE *g=fopen("swap.out","w");
stack <int> S;
int N;
char c[90005];
int nr,i,cost;
bool M;
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(c+1,90005,f);
    for(i=1;i<=N;i++)
    {
        if(c[i]=='(')
        {
            S.push(i);
        }
        else
        {
            cost+=i-S.top();
            if(S.size()>1&&S.top()==i-1)
            {
                M=1;
                nr++;
            }
            S.pop();
        }
    }
    fprintf(g,"%d\n",cost);
    if(M)
        fprintf(g,"%d\n%d",cost-2,nr);
    else
        fprintf(g,"-1\n0");
    fclose(f);
    fclose(g);
    return 0;
}
