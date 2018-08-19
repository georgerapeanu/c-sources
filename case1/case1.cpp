#include<fstream>
using namespace std;
ifstream f("case1.in");
ofstream g("case1.out");
int main()
{
    int a,g1=0,g2=0,g3=0,b=0,fe=0,c=0,i,n;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(a/1000==1)
            g1++;
        else if(a/1000==2)
            g2++;
        else
            g3++;
        b=b+a/100%10;
        fe=fe+a/10%10;
        c=c+a%10;
    }
    g<<g1<<"\n"<<g2<<"\n"<<g3<<"\n"<<b<<"\n"<<fe<<"\n"<<c;
    f.close();g.close();
    return 0;
}
