#include <iostream>
using namespace std;
int sg(int nr)
{
    if(nr==1)return 0;
    if(nr&1)return sg(nr>>1);
    return nr>>1;
}
int x,y;
int sx,sy;
int main()
{
    while(1)
    {
        cin>>x>>y;
        if(!x||!y)return 0;
        sx=sg(x);
        sy=sg(y);
        if(sx>sy)
        {
            int nr=2*sy;
            while(!((x+1)/2<=nr&&nr<=x))
            {
                nr=2*nr+1;
            }
            cout<<"cutx "<<nr<<"\n";
        }
        else
        {
            int nr=2*sx;
            while(!((y+1)/2<=nr&&nr<=y))
            {
                nr=2*nr+1;
            }
            cout<<"cuty "<<nr<<"\n";
        }
    }
    return 0;
}
