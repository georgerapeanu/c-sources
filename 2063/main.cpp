#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int M,val;
int main()
{
    cin>>M;
    srand(0);
    for(int i=2;i<=M+1;i++)
    {
        for(int j=1;j<i;j++)
        {
            for(int k=j+1;k<=i;k++)
                cout<<"? "<<j<<" "<<k<<"\n";
        }
        val=(rand()%(i-1))+1;
        cout<<"! "<<val<<" "<<val+1<<"\n";
    }
    return 0;
}
