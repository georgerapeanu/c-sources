#include <iostream>
#include <algorithm>
using namespace std;
string a;
int main()
{
    cin>>a;
    a=" "+a;
    for(auto &it:a)it-='0';
    if(a[1]+a[2]+a[3]>a[4]+a[5]+a[6])
        reverse(a.begin()+1,a.end());
    sort(a.begin()+1,a.begin()+4);
    sort(a.begin()+4,a.begin()+7);
    //cout<<a;
    if(a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])==0)cout<<0;
    else if(a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])<=9-a[1]||a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])<=a[6])cout<<1;
    else if(a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])<=18-a[2]-a[1]||a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])<=a[6]+a[5]||a[4]+a[5]+a[6]-(a[1]+a[2]+a[3])<=a[6]+9-a[1])cout<<2;
    else cout<<3;
    return 0;
}
