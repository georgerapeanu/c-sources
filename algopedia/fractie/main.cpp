#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
ifstream f("fractie.in");
ofstream g("fractie.out");
long long j,a,b,c,nc,r,nr,uc,cc;
char v[30];
int main()
{
    f>>a>>b;
    j=0;
    c=a/b;
   r=a%b;
    itoa(cc,v,10);
    f.close();g.close();
    return 0;
}
