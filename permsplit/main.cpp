#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("permsplit.in","r");
FILE *g=fopen("permsplit.out","w");
typedef class{
    public:
    int x;
    int y;
    int ind;
}interval;
stack <interval> s;
stack <int> split;
int n,nr,i;
interval rez;
int main()
{
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&nr);
        rez.ind=i;
        rez.x=rez.y=nr;
        while(!s.empty()&&(rez.y+1==s.top().x||s.top().y+1==rez.x))
        {
            split.push(min(s.top().ind,rez.ind));
            rez.x=min(rez.x,s.top().x);
            rez.y=max(rez.y,s.top().y);
            rez.ind=max(rez.ind,s.top().ind);
            s.pop();
        }
        s.push(rez);
    }
    if(s.size()>1)
    fprintf(g,"-1");
    else
        for(i=1;i<n;i++)
        {
            fprintf(g,"%d ",split.top());
            split.pop();
        }
    fclose(f);
    fclose(g);
    return 0;
}
