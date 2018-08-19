#include <iostream>
using namespace std;
string a[10];
int main()
{
    for(int i=0;i<10;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(a[i][j]!='.')continue;
            int nr=1,x=i,y=j;
            while(x>0&&a[x-1][y]=='X'){nr++;x--;}x=i;
            while(x<9&&a[x+1][y]=='X'){nr++;x++;}x=i;
            if(nr>=5){cout<<"YES";return 0;}
            nr=1;
            while(y>0&&a[x][y-1]=='X'){nr++;y--;}y=j;
            while(y<9&&a[x][y+1]=='X'){nr++;y++;}y=j;
            if(nr>=5){cout<<"YES";return 0;}
            nr=1;
            while(y>0&&x>0&&a[x-1][y-1]=='X'){nr++;y--;x--;}y=j;x=i;
            while(y<9&&x<9&&a[x+1][y+1]=='X'){nr++;y++;x++;}y=j;x=i;
            if(nr>=5){cout<<"YES";return 0;}
            nr=1;
            while(y>0&&x<9&&a[x+1][y-1]=='X'){nr++;y--;x++;}y=j;x=i;
            while(y<9&&x>0&&a[x-1][y+1]=='X'){nr++;y++;x--;}y=j;x=i;
            if(nr>=5){cout<<"YES";return 0;}
        }
    }
    cout<<"NO";
    return 0;
}
