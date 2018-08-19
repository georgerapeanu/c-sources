#include <fstream>
#include <math.h>
using namespace std;
ifstream f("prajituri.in");
ofstream g("prajituri.out");
int n,a,i,ciur[101],nr1,nr2;
int main()
{
    f>>n;
    ciur[2]=ciur[3]=ciur[5]=ciur[7]=ciur[11]=ciur[13]=ciur[17]=ciur[19]=ciur[23]=ciur[29]=ciur[31]=ciur[37]=ciur[41]=ciur[43]=ciur[47]=ciur[53]=ciur[59]=ciur[61]=ciur[67]=ciur[71]=ciur[73]=ciur[79]=ciur[83]=ciur[89]=ciur[97]=1;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(ciur[a]==1)
        nr1++;
        if(sqrt(a)==int(sqrt(a)))
        {
            if(ciur[int(sqrt(a))]==1)
            nr2++;
        }
    }
    g<<nr1<<"\n"<<nr2;
    f.close();g.close();
    return 0;
}
