#include <cstdio>
#include <stack>
#include <iostream>
using namespace std;
FILE *f=fopen("reactii.in","r");
FILE *g=fopen("reactii.out","w");
int N,M;
typedef pair<int,int> interval;
stack<interval> s;
interval rez;
bool can(interval st,interval dr)
{
    if(st.second+1==dr.first||dr.second+1==st.first)
    return 1;
    return 0;
}
interval pereche(interval st,interval dr)
{
     return interval(min(st.first,dr.first),max(st.second,dr.second));
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
            while(!s.empty())
    s.pop();
    int tmp=0;
    rez=interval(0,0);
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%d",&tmp);
            rez=interval(tmp,tmp);
            while(!s.empty()&&can(rez,s.top()))
            {
                rez=pereche(rez,s.top());
                s.pop();
            }
            s.push(rez);
        }
        if(s.size()==1)
            fprintf(g,"1\n");
        else
            fprintf(g,"0\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
