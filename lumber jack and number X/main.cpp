#include <iostream>
#include <cstring>
using namespace std;
char c[100],rez[200];
int i,N,ctr;
int main()
{
    cin.getline(c,100);
    N=strlen(c);
    rez[0]=c[0];ctr=1;
    for(i=1;i<N;i++)
    {
        rez[ctr++]='-';
        rez[ctr++]=c[i];
    }

    cout<<rez;
    return 0;
}
