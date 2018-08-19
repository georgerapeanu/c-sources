#include <iostream>

using namespace std;
int N,K;
bool ok(int pos)
{
    string a,b;
    if(pos==1)
    {
        cout<<1<<" "<<pos<<" "<<pos+1<<endl;
        cin>>a;
        return a=="TAK";
    }
    if(pos==N)
    {
        cout<<1<<" "<<pos<<" "<<pos-1<<endl;
        cin>>a;
        return a=="TAK";
    }
    cout<<1<<" "<<pos<<" "<<pos+1<<endl;cin>>a;
    cout<<1<<" "<<pos<<" "<<pos-1<<endl;cin>>b;
    return a=="TAK"&&b=="TAK";
}
int main()
{
    cin>>N>>K;
    int x,y;
    int st=1,dr=N;
    while(st<dr)
    {
        int mid=(st+dr)/2;
        string a;
        cout<<1<<" "<<mid<<" "<<mid+1<<endl;
        cin>>a;
        if(a=="TAK")dr=mid;
        else st=mid+1;
    }
    x=st;
    st=1,dr=x-1;
    while(st<dr)
    {
        int mid=(st+dr)/2;
        string a;
        cout<<1<<" "<<mid<<" "<<mid+1<<endl;
        cin>>a;
        if(a=="TAK")dr=mid;
        else st=mid+1;
    }
    if(!ok(st)||dr==0)
    {
        st=x+1;dr=N;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            string a;
            cout<<1<<" "<<mid<<" "<<mid+1<<endl;
            cin>>a;
            if(a=="TAK")dr=mid;
            else st=mid+1;
        }
    }
    y=st;
    cout<<2<<" "<<x<<" "<<y<<endl;
    return 0;
}
