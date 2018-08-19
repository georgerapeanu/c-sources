#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("turn.in","r");
FILE *g=fopen("turn.out","w");
stack <pair<short,int> > S;
stack <short> tmp;
int N,i,K,nr;
short val,fval=-1;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    fscanf(f,"%hd",&fval);
    while(i<N)
    {
        nr=1;
        do
        {
            nr++;
            fscanf(f,"%hd",&val);
            i++;
        }
        while(i<N&&fval==val);
        nr--;
        if(fval!=-1)
        {
            if(!S.empty()&&fval==(S.top()).first)
            {
                (S.top()).second+=nr;
                if((S.top()).second>=K)
                    S.pop();
            }
            else
            {
                S.push(make_pair(fval,nr));
                if((S.top()).second>=K)
                    S.pop();
            }
        }
        fval=val;
    }
    while(!S.empty())
    {
        while((S.top()).second)
        {
            tmp.push((S.top()).first);
            (S.top()).second--;
        }
        S.pop();
    }
    fprintf(g,"%d\n",tmp.size());
    while(!tmp.empty())
        {fprintf(g,"%hd ",tmp.top());tmp.pop();}
    fclose(f);
    fclose(g);
    return 0;
}
