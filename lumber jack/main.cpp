#include <iostream>
#include <cstring>
using namespace std;
char c[105],rez[205];
int ctr,i,l;
int main()
{
    cin.getline(c,105);
    l=strlen(c);
    for(i=0;i<l;i++)
    {
        if(c[i]!='.'&&c[i]!='-'&&c[i]!='\n')
        {
            if(c[i]==',')
            {rez[ctr++]=' ';}
            rez[ctr++]=c[i];
        }
    }
    cout<<rez;
    return 0;
}
