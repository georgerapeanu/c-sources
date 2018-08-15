#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
FILE *f=fopen("bool.in","r");
FILE *g=fopen("bool.out","w");
map<char,bool> val;
string C;
int ind=1;
int N;
char V[105];
bool legor();
bool legand();
bool getterm()
{
    if(C[ind]=='!')
    {
        ind++;
        return !getterm();
    }
    if(C[ind]=='(')
        {ind++;bool val=legor();ind++;return val;}
    if(C[ind]=='1')
        {ind++;return 1;}
    if(C[ind]=='0')
        {ind++;return 0;}
    return val[C[ind++]];
}
bool legand()
{
    bool val=getterm();
    while(C[ind]=='&')
    {
        ind++;
        val=val&getterm();
    }
    return val;
}
bool legor()
{
    bool val=legand();
    while(C[ind]=='|')
    {
        ind++;
        val=val|legand();
    }
    return val;
}
int main()
{
    freopen("bool.in","r",stdin);
    getline(cin,C);
    for(int i=0;i<C.size();i++)
    {
        if(C[i]=='N'&&C[i+1]=='O'&&C[i+2]=='T'){C.erase(i+1,2);C[i]='!';}
        else if(C[i]=='O'&&C[i+1]=='R'){C.erase(i+1,1);C[i]='|';}
        else if(C[i]=='A'&&C[i+1]=='N'&&C[i+2]=='D'){C.erase(i+1,2);C[i]='&';}
        else if(C[i]==' ') {C.erase(i,1);i--;}
        else if(C[i]=='T'&&C[i+1]=='R'){C.erase(i+1,3);C[i]='1';}
        else if(C[i]=='F'&&C[i+1]=='A'){C.erase(i+1,4);C[i]='0';}
    }
    cin>>N;
    cin.getline(V+1,105);
    cin.getline(V+1,105);
    for(int i=1;i<=N;i++)
    {
        val[V[i]]^=1;
        ind=0;
        fprintf(g,"%d",legor());
    }
    fclose(f);
    fclose(g);
    return 0;
}
