#include<iostream>
using namespace std;
long su[10000];
int main()
{
    long w=0,e,d,k,n,p,i,j,s2=0,s=0,l,a=0,q;
    cin>>n>>k>>p;
    w=0;
    for(i=1;i<=n;i++)
    {
        s=0;
        a=0;
        for(j=1;j<=i;j++)
        {
           s=s+j;
           w++;
           if(w==p)
           {
               q=j;
               e=i;
           }
        }
        for(l=1;l<=s;l++)
        {
            if(s%l==0)
                a++;
        }
        if(a>=k)
            su[i]=s;
    }
    s=0;
    for(i=0;i<=9999;i++)
    {
       s=s+su[i];
    }
    if(s==0)
    {
      for(i=1;i<=n;i++)
      {
          for(j=1;j<=i;j++)
          {
              s=s+j;
          }
          if(s%2==0)
            s2=s2+s;
            s=0;
      }
    }
    if(s!=0)
    cout<<"a)"<<s;
    else
    cout<<"a)"<<s2;
    cout<<"\nb)"<<q;
    cout<<"\nc)"<<e;
    return 0;

}
