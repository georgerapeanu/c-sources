#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("secv6.in","r");
FILE *g=fopen("secv6.out","w");
int N;
int X[8192];
stack<int> S;
long long rez;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=0;i<N&&i<8192;i++)
        fscanf(f,"%d",&X[i]);
    for(int i=0;i<N;i++)
    {
        int val=i+(X[i/8192]^X[i%8192]);
        while(!S.empty()&&S.top()<val)
        {
            S.pop();
            rez++;
        }
        if(S.empty())S.push(val);
        else
        {
            if(S.top()==val);
            else S.push(val);
            rez++;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
