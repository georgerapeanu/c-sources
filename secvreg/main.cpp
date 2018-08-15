#include <cstdio>
#include <cassert>
#include <cstring>
#include <map>
#include <deque>
#define NMAX 1000000
using namespace std;
FILE *f=fopen("secvreg.in","r");
FILE *g=fopen("secvreg.out","w");
int st,dr,N,M,sti,dri,tmp;
deque<int> dq;
deque<char> dc;
char C[NMAX],c;
map <char,char> inv;///facem un deque de caractere si unul de indici
///ii foarte ok sa eliminam subsirurile corect parantezate din subsecventa initiala si din care o sa vina,pentru ca este clar ca tot corect parantezate vor ramana si la queriuri
int main()
{
    inv['(']='0';///nu are sens inversul la ( sau [,din moment ce este folosit doar la inserarea la final(daca ar avea sens,ar considera ][ o parantezare corecta)
    inv[')']='(';
    inv['[']='0';
    inv[']']='[';
    fgets(C+1,NMAX,f);
    N=strlen(C+1);
    sti=1;
    dri=N;
    while(sti<=dri&&(C[dri]=='\n'||C[dri]=='\0'))
        dri--;
    for(int i=sti;i<=dri;i++)
    {
        if(!dc.empty()&&dc.back()==inv[C[i]])
        {
            dc.pop_back();
            dq.pop_back();
        }
        else
        {
            dc.push_back(C[i]);
            dq.push_back(i);
        }
        assert(dc.size()==dq.size());
    }
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %c",&tmp,&c);
        if(tmp==0)
        {
            sti--;
            if(!dc.empty()&&((dc.front()==')'&&c=='(')||(dc.front()==']'&&c=='[')))
            {
                fprintf(g,"%d\n",dq.front()-sti+1);
                dq.pop_front();
                dc.pop_front();
            }
            else
            {
                fprintf(g,"0\n");
                dq.push_front(sti);
                dc.push_front(c);
            }
        }
        else
        {
            dri++;
            if(!dc.empty()&&((dc.back()=='['&&c==']')||(dc.back()=='('&&c==')')))
            {
                fprintf(g,"%d\n",dri-dq.back()+1);
                dq.pop_back();
                dc.pop_back();
            }
            else
            {
                fprintf(g,"0\n");
                dq.push_back(dri);
                dc.push_back(c);
            }
        }
        assert(dc.size()==dq.size());
    }
    fclose(f);
    fclose(g);
    return 0;
}
