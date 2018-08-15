#include <iostream>
#include <cstdlib>

using namespace std;
char c1,c2,c;
int nrcf()
{
    long long nr=1;
    int cf=1;
    while(1)
    {
        cout<<"? "<<nr<<endl;
        cin>>c;
        if(c=='N')return cf-1;
        cf++;
        nr*=10;
    }
}
void particular()
{
    long long nr=1,rez;
    for(int i=1;i<=10;i++)
    {
        cout<<"? "<<nr<<endl;
        cin>>c;
        if(c=='N')return;
        nr*=10;
    }
    nr=9;rez=1;
    for(int i=1;i<=10;i++)
    {
        cout<<"? "<<nr<<endl;
        cin>>c;
        if(c=='Y')
        {
            cout<<"! "<<rez<<endl;exit(0);
        }
        nr=nr*10+9;
        rez=rez*10;
    }
}
int main()
{
    particular();
    int nr=nrcf();
    long long st=1;
    for(int i=1;i<nr;i++)st=10*st;
    long long dr=10*st-1;
    while(st<dr)
    {
        long long mid=(st+dr)/2;
        cout<<"? "<<mid*10+1<<endl;
        cin>>c;
        if(c=='Y')dr=mid;
        else st=mid+1;
    }
    cout<<"! "<<st<<endl;
    return 0;
}
