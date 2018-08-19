#include<fstream>
#include<iostream>
using namespace std;
ifstream f("psp.in");
ofstream g("psp.out");
int main()
{
    int s=0,is=0,n,j,m,i,l=0;
    f>>j>>m;
    for(i=1;i<=j;i++)
    {
        f>>n;
        is=s;
        is=is+n;
        if(is<=m)
        {
            s=is;
            l++;
        }
    }
    s=m-s;
    g<<l<<" "<<s;
    f.close();g.close();
    return 0;
}
