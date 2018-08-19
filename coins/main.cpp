#include <iostream>
using namespace std;
int N;
int x,y;
int main()
{
    cin>>N;
    cout<<0<<" "<<0<<"\n";
    cout.flush();
    while(cin>>x>>y)
    {
        cout<<-x<<" "<<-y<<"\n";
        cout.flush();
    }
    return 0;
}
