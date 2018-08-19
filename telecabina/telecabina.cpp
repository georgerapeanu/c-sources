#include<fstream>
#include<iostream>
using namespace std;
ifstream f("cabina.in");
ofstream g("cabina.out");
int main()
{
    int n,a=0,b,i=1,s=0,c=0,l=0,d=0,m=0;
    f>>n;
    while(i<=n)
    {
        c=a;
        f>>a>>b;
        s=s+b;
        if(c<a&&c!=0)
        l=l+(a-c)*3;
        else if(c>a&&c!=0)
        l=l+c-a;
        if(d!=0)
        {
            if(d<c&&c>a)
                m++;
            else if(d>c&&c<a)
                m++;
                  cout<<d<<" "<<c<<" "<<a<<" "<<m<<"\n";
        }
        d=c;
        i++;
}
    g<<s<<endl;
    g<<l<<endl;
    g<<m;
   f.close();g.close();
   return 0;
}
