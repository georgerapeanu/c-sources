#include<iostream>
using namespace std;
int main()
{
    int n,c=0,i,e=0;
    cout<<"numarul de zile:";
    cin>>n;
    for(i=1;i<=n;i++)
    {
         e=e*10+1;
         c=c+7*e;
    }
   cout<<"dupa "<<n<<" zile cangurul va sari  "<<c<<" metri";
    return 0;
}
