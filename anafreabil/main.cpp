#include <fstream>
using namespace std;
ifstream f("anagramabil.in");
ofstream g("anagramabil.out");
unsigned long long int n,cn,c[10],nc[10],gasit,uc,j,gasitda,i;
int main()
{
    f>>n;
    cn=n;
    while(cn!=0)
    {
        uc=cn%10;
        c[uc]++;
        cn=cn/10;
    }
    for(i=2;i<=9;i++)
    {
        gasit=0;
        cn=i*n;
    while(cn!=0)
    {
        uc=cn%10;
        nc[uc]++;
        cn=cn/10;
    }
    for(j=0;j<=9;j++)
    {
        if(c[j]!=nc[j])
        {
            gasit=1;
            break;
        }
    }
    if(gasit==0)
    {
        if(gasitda==0)
        {
            gasitda=1;
            g<<"DA \n";
        }
        g<<i;
    }
    for(j=0;j<=9;j++)
    {
        nc[j]=0;
    }
    }
    if(gasitda==0)
        g<<"NU";
    return 0;
}
