#include <fstream>
using namespace std;
ofstream g("ciur.out");
bool ciur[201];
short i,j;
int main()
{
    ciur[0]=ciur[1]=true;
    for(i=2;i<=200;i++)
    if(ciur[i]==0)
    {
        for(j=i+i;j<=200;j+=i)
        ciur[j]=true;
    }
    for(i=0;i<=200;i++)
    g<<ciur[i]<<",";
    g.close();
    return 0;
}
