#include <fstream>
#include <iostream>
using namespace std;
ifstream f("comp.in");
ofstream g("comp.out");
char c;
short op[250],nr3;
bool gasit,comp,adev[1000];
long long nr2,nr,n,v[250],l,i,j;
int main()
{
    f>>n;
    c=f.get();
    while(c!=-1)
    {
        c=f.get();nr2=0;
        while(c>='0'&&c<='9')
        {
            nr2=nr2*10+c-'0';c=f.get();
        }
        if(c=='m')
        nr+=nr2*1000;
        else if(c=='s')
        nr+=nr2*100;
        else if(c=='z')
        nr+=nr2*10;
        else if(c=='u')
        nr+=nr2;
        else
        {
            v[l]=nr;nr=0;
            if(c=='+')
            op[l]=-1;
            else if(c=='<')
            {comp=op[l]=0;nr3++;}
            else if(c=='>')
            comp=op[l]=1;
            l++;
            if(c=='\n')
            {
                nr=v[0];nr2=0;
                for(i=1;i<l;i++)
                {
                     if(op[i-1]==-1&&gasit==false)
                     {
                         nr+=v[i];
                     }
                     if(op[i-1]==0||op[i-1]==1)
                     {gasit=true;nr2=v[i];i++;}
                     if(i<l&&gasit==true)
                     if(op[i-1]==-1)
                     nr2+=v[i];
                }
                if(nr<nr2&&comp==0)
                adev[j++]=1;
                else if(nr>nr2&&comp==1)
                adev[j++]=1;
                else
                adev[j++]=0;
                nr=0;gasit=false;l=0;
            }
        }

    }
   g<<nr3<<"\n";
    for(i=0;i<j;i++)
    g<<adev[i]<<"\n";
    f.close();g.close();
    return 0;
}
