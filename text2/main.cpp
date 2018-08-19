#include <cstdio>
#include <set>
using namespace std;
FILE *f=fopen("text2.in","r");
FILE *g=fopen("text2.out","w");
int N,i,maxim,nr,cuv=1,rez;
set <int> S;
char c,fc;
bool folosit[27];
int main()
{
    fscanf(f,"%d\n",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%c",&c);
        if(c=='*')
        {
                  if(nr>maxim)
                {maxim=nr;S.clear();S.insert(cuv);}
            else if(nr==maxim)
                {S.insert(cuv);};
            nr=0;
             if(fc!='*')
                cuv++;
            fc=0;
        }
        else
        {
            if(fc>c)
                {
                    if(nr>maxim)
                {maxim=nr;S.clear();S.insert(cuv);}
            else if(nr==maxim)
                {S.insert(cuv);};
                    nr=1;
                }
            else
                nr++;

            if(!folosit[c-'a'+1])
                {rez++;folosit[c-'a'+1]=1;}
        }
        fc=c;
    }
    fprintf(g,"%d\n",S.size());
    for(set<int> ::iterator it=S.begin();it!=S.end();it++)
        fprintf(g,"%d ",*it);
    fprintf(g,"\n%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
