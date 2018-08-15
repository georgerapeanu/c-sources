#include <fstream>
#include <cstring>
using namespace std;
ifstream f("piramida.in");
ofstream g("piramida.out");
char nume[80];
int i,cifra[80],suma,j;
int main()
{
    f>>nume;g<<nume<<"\n";
    for(i=0;i<strlen(nume);i++)
        {
            if(nume[i]>='A'&&nume[i]<='Z')
            cifra[i]=(nume[i]-'A')%9+1;
            else
              cifra[i]=(nume[i]-'a')%9+1;
            g<<cifra[i]<<" ";
        }
    for(j=0;j<strlen(nume);j++)
    {
        g<<"\n";
        for(i=0;i<=j;i++)
            g<<" ";
    for(i=0;i<strlen(nume)-j-1;i++)
    {
        suma=cifra[i]+cifra[i+1];
        if(suma>9)
            suma=suma/10+suma%10;
        cifra[i]=suma;
        g<<suma<<" ";
    }
    }
    f.close();g.close();
    return 0;
}
