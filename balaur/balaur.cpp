#include<iostream>
using namespace std;
int main()
{
    int n,m,i=6;
    cout<<"numarul de zile este:";
    cin>>n;
    for(m=1;m<n;m++)
    {
        i=i+(6-1);
    }
    i=i-1;
    cout<<"dupa "<<n<<" zile,balaurul are "<<i<<" capete";
    return 0;
}
