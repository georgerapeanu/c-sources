#include <iostream>
#include <cstring>
using namespace std;
char C[200],fost;
int i,nr,N,rez;
int main()
{
    C[0]='.';
    cin.getline(C+1,200);
    N=strlen(C);
    for(i=1;i<N;i++)
    {
        if(nr==5)
        {
            rez++;
            nr=1;
        }
        else if(C[i]!=fost&&fost!='\0')
        {
             nr=1;
             rez++;
        }
        else
        {
            nr++;
        }
        fost=C[i];
    }
    cout<<rez+1;
    return 0;
}
