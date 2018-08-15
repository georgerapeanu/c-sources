#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
FILE *f=fopen("ecp.in","r");
FILE *g=fopen("ecp.out","w");
typedef struct {int x,y,z;} data;
stack<data> S;
data C[124];
int i;
int N;
data X,a;
char c[1005];
int main()
{
    fgets(c+1,1000,f);
    C[40]={1,0,0};
    C[91]={0,2,0};
    C[123]={0,0,4};
    c[0]='.';
    N=strlen(c);
    S.push({0,0,0});
    for(i=1;i<N;i++)
    {
        if(c[i]=='(')
        {
            if(c[i-1]=='('||c[i-1]=='['||c[i-1]=='{')
            {
                X=S.top();
                S.pop();
                X={X.x+C[c[i-1]].x,X.y+C[c[i-1]].y,X.z+C[c[i-1]].z};
                S.push(X);
            }
            a=S.top();
            S.push({0,0,0});
        }
        else if(c[i]=='[')
        {
            if(c[i-1]=='('||c[i-1]=='['||c[i-1]=='{')
            {
                X=S.top();
                S.pop();
                X={X.x+C[c[i-1]].x,X.y+C[c[i-1]].y,X.z+C[c[i-1]].z};
                S.push(X);
            }
            a=S.top();
            S.push({0,0,0});
        }
        else if(c[i]=='{')
        {
            if(c[i-1]=='('||c[i-1]=='['||c[i-1]=='{')
            {
                X=S.top();
                S.pop();
                X={X.x+C[c[i-1]].x,X.y+C[c[i-1]].y,X.z+C[c[i-1]].z};
                S.push(X);
            }
            S.push({0,0,0});
        }
        else if(c[i]==')')
        {
            X=S.top();
            S.pop();
             a=S.top();
            S.pop();
            S.push({X.x+a.x+1,X.y+a.y,X.z+a.z});
        }
        else if(c[i]==']')
        {
            X=S.top();
            S.pop();
            a=S.top();
            S.pop();
              S.push({X.x+a.x,X.y+a.y+1,X.z+a.z});
        }
        else if(c[i]=='}')
        {
            X=S.top();
            S.pop();
               a=S.top();
            S.pop();
              S.push({X.x+a.x,X.y+a.y,X.z+a.z+1});
        }
    }
    fprintf(g,"%d %d %d",(S.top()).x,(S.top()).y,(S.top()).z);
    fclose(f);
    fclose(g);
    return 0;
}
