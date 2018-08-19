#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;
FILE *f=fopen("evaluare1.in","r");
FILE *g=fopen("evaluare1.out","w");
char C[105];
int ind;
long long expr();
long long lgpow(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1)
            p*=b;
        b*=b;
        e>>=1;
    }
    return p;
}
long long val()
{
    if(C[ind]=='!')
    {
        ind++;
        long long nr=val();
        long long rez=0;
        while(nr)
        {
            rez=rez*10+nr%10;
            nr/=10;
        }
        return rez;
    }
    if(C[ind]=='(')
    {
        ind++;
        long long tmp=expr();
        ind++;
        return tmp;
    }
    long long rez=0;
    while(isdigit(C[ind]))
    {
        rez=rez*10+C[ind]-'0';
        ind++;
    }
    return rez;
}
long long putere()
{
    vector<long long> tmp;
    tmp.clear();
    tmp.push_back(val());
    while(C[ind]=='^')
    {
        ind++;
        tmp.push_back(val());
    }
    int l=tmp.size();
    while(l!=1)
    {
        long long e=tmp[l-1];
        long long b=tmp[l-2];
        tmp[l-2]=lgpow(b,e);
        l--;
    }
    return tmp[0];
}
long long term()
{
    long long nr=putere();
    while(C[ind]=='/')
    {
        ind++;
        nr/=putere();
    }
    return nr;
}
long long expr()
{
    long long nr=term();
    while(C[ind]=='+')
    {
        ind++;
        nr+=term();
    }
    return nr;
}
int main()
{
    fgets(C+1,105,f);
    ind=1;
    fprintf(g,"%lld",expr());
    fclose(f);
    fclose(g);
    return 0;
}
