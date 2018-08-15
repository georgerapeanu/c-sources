#include<iostream>
using namespace std;
int main()
{
  int s=0,i,l,z,uc,n;
  cout<<"n=";
  cin>>n;
  for(i=1;i<=n;i++)
{
    l=1;
    for(z=1;z<=i;z++)
    {
        l=l*i;
    }
    s=s+l;
}
uc=s%10;
cout<<"\n"<<uc;
return 0;
}
