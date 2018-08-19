#include <iostream>
using namespace std;
int main()
{
    int n=20,x=1,y=1,hold;
    for(int i=3;i<=n;i++)
    {
        hold=y;
        y+=x;
        x=hold;
    }
    cout<<y;
    return 0;
}
