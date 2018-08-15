#include<fstream>
#include<iostream>
using namespace std;
ifstream f("iepurasi.in");
ofstream g("iepurasi.out");
int n,a[10001],i,maxim[10001],j,hold,k=0,operatie;
int main()
{
    f>>n;
    for(i=0;i<n;i++) {f>>a[i];maxim[i]=a[i];}
    for(i=0;i<n-1;i++)
  {
   for(j=0;j<n-1;j++)
   {
    if (maxim[j]<maxim[j+1])
    {
    hold = maxim[j];
    maxim[j]=maxim[j+1];
    maxim[j+1]=hold;
    }
   }
  }
  for(i=0;i<n;i++)
    {
        if(v[i]==maxim[k])
        {
            if(k!=i)
            {

            }
            k++;
        }
    }
    f.close();g.close();
    return 0;
}
