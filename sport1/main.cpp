#include <fstream>
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
ifstream f("sport1.in");
ofstream g("sport1.out");
long long a,b,t1,t2,t3,r;
double s,n,m;
int main()
{
    f>>a>>b>>n;i=3;
    s=a+b;

    m=s/n;
    g<<m;
    f.close();
    g.close();
    return 0;
}
