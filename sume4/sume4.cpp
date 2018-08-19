#include<fstream>
using namespace std;
ifstream f("sume4.in");
ofstream g("sume4.out");
int main()
{
    int n,a,b,c,sa=0,sm=0,i,l;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>l;
        a=l/1000;
        b=l/100%10;
        c=l%100;
        sa=sa+a;
        sm=sm+c;
        if(a<c)    sa=sa+b;
        if(a>c)    sm=sm+b;
    }
    g<<sa<<" "<<sm;
    f.close();g.close();
    return 0;
}

