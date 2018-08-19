#include <fstream>
#include <stack>
using namespace std;
ifstream f("bile3.in");
ofstream g("bile3.out");
int sir1[2010],sir2[2010],i,N,j,contor;
stack <int> s;
char rez[4100];
int main()
{
    f>>N;
    for(i=1;i<=N;i++)
        f>>sir1[i];
    for(i=1;i<=N;i++)
        f>>sir2[i];
    i=1;
    j=1;
    while(i<=N&&j<=N)
    {
         while(sir1[j-1]!=sir2[i])
            {
            s.push(sir1[j]);
            rez[contor++]='I';
            j++;
            }
        while(!s.empty()&&s.top()==sir2[i])
        {
            s.pop();
            i++;
            rez[contor++]='O';
        }
    }
    if(s.empty())
    g<<rez;
    else
    g<<"imposibil";
    f.close();
    g.close();
    return 0;
}
