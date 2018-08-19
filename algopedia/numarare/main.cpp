#include <fstream>
#include <cstring>
using namespace std;
ifstream f("numarare.in");
ofstream g("numarare.out");
char v[1000000];
long long i,nrcuv,nrcf;
int main()
{
    while(!f.eof())
    {
        f.getline(v,1000000);
        for(i=0;i<strlen(v);i++)
        {
           if(v[i]>='a'&&v[i]<='z')
           {
               nrcuv++;
               while(v[i]>='a'&&v[i]<='z')
               i++;
               i--;
           }
           if(v[i]>='0'&&v[i]<='9')
           {
               nrcf++;
               while(v[i]>='0'&&v[i]<='9')
               i++;
               i--;
           }
        }
    }
    g<<nrcuv<<"\n"<<nrcf;
    f.close();g.close();
    return 0;
}
