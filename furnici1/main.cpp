#include <fstream>
using namespace std;
ifstream f("furnici1.in");
ofstream g("furnici1.out");
long long int maxim,i,l,v[10000000],n,a,x,y,j,temp;
char c[10000000],b;
int main()
{
    int flag=1;
    f>>l>>n;
    for(i=1;i<=l;i++)
    {
        f>>a>>b;v[i]=a;c[i]=b;
    }
    for(i = 1; (i <= l) && flag; i++)
     {
          flag = 0;
          for (j=0; j < (l -1); j++)
         {
               if (v[j+1] > v[j])
              {
                    temp = v[j];
                    v[j] = v[j+1];
                    v[j+1] = temp;
                    temp = c[j];
                    c[j] = c[j+1];
                    c[j+1] = temp;
                    flag = 1;
               }
          }
     }
    for(i=1;i<l;i++)
    {
        if(c[i]!=c[i+1])
        {
            x=v[i];y=v[i]-v[i+1]+l-v[i+1];
            if(x>maxim)
                maxim=x;
            if(y>maxim)
                maxim=y;
        }
    }
    g<<maxim;
    f.close();g.close();
    return 0;
}
