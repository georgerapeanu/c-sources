#include<fstream>
using namespace std;
ifstream f("triunghi1.in");
ofstream g("triunghi1.out");
int main()
{
    int i,j,c,l,cat,r=0,s=0;
    f>>l>>c;
    s=l*(l-1)/2;
    r=s+c;
     if(r>9)
        r=r%9;
        if(r==0)
            r=9;
     g<<r;
        f.close();g.close();
    return 0;
}
