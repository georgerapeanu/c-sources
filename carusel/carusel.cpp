#include<fstream>
using namespace std;
ifstream f("carusel.in");
ofstream gi("carusel.out");
int v[50],a[100];
int main()
{
    int n,g,i,j=0,k,s=0,s2=0;
    f>>n>>g;
    for(i=0;i<g;i++)
    {
        f>>v[i];
        s+=v[i];
    }
    for(i=0;i<g;i++)
    {
            while(v[i]>1)
            {
               if(j>=n)
               {
                   for(k=0;k<n;k++)
                   {
                       if(a[k]==1)
                       {
                           a[k]=2;s2+=1;
                       }
                       if(s2==s)
                        k=n;
                   }
               }
              a[j]=2;s2+=2;
              v[i]=v[i]-2;
              if(v[i]!=0)
                j++;
            }
            if(v[i]==1)a[j]=1;j++;s2+=1;
    }
    for(i=0;i<n;i++)
        gi<<a[i]<<"\n";
    f.close();gi.close();
    return 0;
}
