#include<iostream>
using namespace std;
int main()
{
    int x,y,z=0,m;
    for(x=100;x<=10000;x++)
    {
        m=x;
        y=0;
        while(m>9)
        {
        y=y*100+(m%100)/10*10+m%10;
        m=m/100;
        }

        if(x==y) {z=z++;
        cout<<x<<" "<<y<<endl;}
         }
    cout<<z;
    return 0;
}
