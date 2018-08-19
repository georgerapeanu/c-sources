#include <fstream>
using namespace std;
ifstream f("genab.in");
ofstream g("genab.out");
char x[21];
int n;
void afisare()
{
    int i;
    for (i=1;i<=n;i++)
    {
      g<<x[i];
    }
    g<<"\n";
}
void generare(int k)
{
    if(k==n+1)
        afisare();
    else
    {
        x[k]='a';
        generare(k+1);
        x[k]='b';
        if(x[k]!=x[k-1])
        generare(k+1);
    }
}

int main()
{
     f>>n;
     generare(1);
     f.close();g.close();
    return 0;
}
