#include <fstream>
#include <cstring>
using namespace std;
ofstream g("rez.out");
char v[4096],c[4096],d;
void resetare()
{
    for(long i=0;i<strlen(v);i++)
    v[i]=c[i]='\0';
}
int main()
{
    ifstream f("-spioni.out");
    ifstream f1("-spioni.ok");
    d=f.get();
    d=f.get();
    f.getline(v,4096);
    f1.getline(c,4096);
    g<<comparare()<<"\n";
    f.close();
    f1.close();
    return 0;
}
