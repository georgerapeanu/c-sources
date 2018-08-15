#include<fstream>
using namespace std;
ifstream f("daruri.in");
ofstream g("daruri.out");
int main()
{
    int t,l,r,ct,cl;
    f>>t>>l;
    ct=t;cl=l;
    r=ct%cl;
    while(r!=0)
    {
        ct=cl;
        cl=r;
        r=ct%cl;
    }
    if(cl!=1)
    {
        g<<cl<<"\n"<<(t/cl)<<" "<<(l/cl);
    }
    else
    {
        g<<0<<"\n"<<0<<" "<<0;
    }
    f.close();g.close();
    return 0;
}
