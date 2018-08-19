#include<fstream>
#include<iostream>
using namespace std;
ifstream f("t.in");
ofstream g("t.out");
long v[3200],maxi=0,hold,i,j,n;
int main()
{
    f>>n;
    for(i=0;i<n;i++)  f>>v[i];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(v[i]<v[j])
            {
                hold=v[i];
                v[i]=v[j];
                v[j]=hold;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if((v[i]!=maxi)||(i==0))
            {
            g<<v[i]<<" ";
            maxi=v[i];
            }
    }
    f.close();g.close();
    return 0;
}
