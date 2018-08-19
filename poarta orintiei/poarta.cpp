#include<iostream>
using namespace std;
int main()
{
    int s,i,l,x=0,j,hold;
    cout<<" ";
    cin>>s;
    int p[s],d[s],q[s];
    for(i=0;i<s;i++)
    {
        cout<<" ";
        cin>>l;
        p[i]=(l+s-i-1)%10;
    }
    for(i=0;i<=s-1;i++)
    {
   for(j=0;j<=s-1;j++)
   {
       if(p[j+1]<p[j])
          {
              hold=p[j];
              p[j]=p[j+1];
              p[j+1]=hold;
          }
   }
    }
    for(i=0;i<s;i++)
    {
        if(p[i]!=p[i+1])
        {
        if(p[i]==0&&i==0)
        {
            cout<<p[i+1]<<p[i];
            i++;
        }
        else
            cout<<p[i];
        }
    }
    return 0;
}
