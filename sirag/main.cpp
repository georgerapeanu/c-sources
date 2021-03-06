#include <cstdio>
#include <algorithm>
#define nmax 100005
using namespace std;
FILE *f=fopen("sirag.in","r");
FILE *g=fopen("sirag.out","w");
int V[nmax],i,N,K;
long long st,dr,mid,last;
bool ok(long long l)  ///lungimea testata
{
    long long a=l/K;  ///nr de secvente complete care trebuie avute
    int x=l%K;  ///nr de culori care apar de a+1 ori
    int y=K-x;  ///nr de culori care apar de a ori
    long long p=0;    ///nr de bile care pot fi distribuite
    for(i=1;i<=N;i++) ///pentru fiecare culoare
    {
        if(x>0)
        {
            if(V[i]>=a+1) ///daca putem distribui a+1 bile din culoarea i
            {
                x--;
                if(p>=a&&x==0)
                {
                    p-=a;
                    y--;
                }
            }
            else  ///daca nu poate putem folosi o parte mai incolo
            {
                p+=V[i];
                if(p>=a+1) ///daca cu tot cu acestea putem distribui
                {
                    p-=a+1;
                    x--;
                    if(p>=a&&x==0)
                    {
                        p-=a;
                        y--;
                    }
                }
            }
        }
        else if(V[i]>=a)///daca am distribuit toate culorile care trebuie sa apara de a + 1 ori,le distribuim pe cele de a ori
            y--;
        else
        {
            p+=V[i];
            if(p>=a)
            {
                p-=a;
                y--;
            }
        }
    }
    return (y<=0);///daca am distribui tot ce puteam
}
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        dr+=V[i];
    }
    st=1;
    last=-1;
    sort(V+1,V+1+N,cmp);
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(ok(mid))
        {
            st=mid+1;
            last=mid;
        }
        else
            dr=mid-1;
    }
    fprintf(g,"%lld",last);
    fclose(f);
    fclose(g);
    return 0;
}
