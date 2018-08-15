#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
ifstream f("romb.in");
ofstream g("romb.out");
char v[202001];
char c;
int n,i=0,s,j,k;
int functie(int j)
{
    g<<v[s+(n*k)];
        k++;j++;
        if (j%n ==0)
        {
            k=0;
            g<<"\n";
            s = s+n-1;
        }
        if(j+1>n*n)  return 0;
        functie(j);
}
int main()
{
    f>>n;

    while (!f.eof())
        f.getline(v, 202001);
    i = 0;
    s=n/2;
    k = 0;
 functie(0);
    f.close();g.close();
    return 0;
}
