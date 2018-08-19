#include <iostream>

using namespace std;
int pos10,pos30;
void cauta10(int st,int dr)
{
    bool val;
    if(st==dr)
        pos10=st;
    int mid=(st+dr)/2;
    cout<<Q<<" "<<(dr-st+1)/2<<" "<<(dr-st+1)/2+(dr-st+1)%2<<" ";
    for(int i=st;i<=mid;i++)
        cout<<i<<" ";
    for(int i=mid+1;i<=dr;i++)
        cout<<i<<" ";
    cout<<"\n";
    cin>>val;
    cout.flush();
    if(val==-1)
    {
        cauta10(st,mid);
        cauta30(mid+1,dr);
    }
    else if(val==1)
    {
        cauta10(mid+1,dr);
        cauta30(st,mid);
    }
    else
    {
        cauta2(st,mid);
        cauta2(mid+1,dr);
    }
}
void cauta30(int st,int dr)
{
    bool val;
    if(st==dr)
        pos30=st;
    int mid=(st+dr)/2;
    cout<<Q<<" "<<(dr-st+1)/2<<" "<<(dr-st+1)/2+(dr-st+1)%2<<" ";
    for(int i=st;i<=mid;i++)
        cout<<i<<" ";
    for(int i=mid+1;i<=dr;i++)
        cout<<i<<" ";
    cout<<"\n";
    cin>>val;
    cout.flush();
    if(val==-1)
    {
        cauta10(st,mid);
        cauta30(mid+1,dr);
    }
    else if(val==1)
    {
        cauta10(mid+1,dr);
        cauta30(st,mid);
    }
    else
    {
        cauta2(st,mid);
        cauta2(mid+1,dr);
    }
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
