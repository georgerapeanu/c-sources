#include<iostream>
#include<fstream>
using namespace std;
ifstream f("sir de caractere.in");
ofstream g("sir de caractere.out");
char c[1],v[100],i=0,l,k=0,a[500],gasit=0,d;
int main()
{    while(!f.eof())
        {
        while(f>>c)
        {
            if(!f.getline(c,1))
            {
       cout<<c<<" ";
       i++;
            }
        }
        cout<<'\n';
        }
       /* for(i=0;i<l;i++)
            cout<<a[i];*/
    f.close();g.close();
    return 0;
}
