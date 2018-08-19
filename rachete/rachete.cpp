#include<fstream>
#include<algorithm>
using namespace std;
ifstream f("rachete.in");
ofstream g("rachete.out");
int main()
{
    long n,i;
    f>>n;
    long v[n];
    for(i=0;i<n;i++)
        f>>v[i];
    sort(v,v+n);
    for(i=0;i<n;i++)
        g<<v[i]<<" ";
    f.close();g.close();
    return 0;
}
