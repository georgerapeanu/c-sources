#include <iostream>

using namespace std;
string a;
long long b,c,wait;
int main()
{
    cin>>a;
    int ind=0;
    while(ind<a.size()&&a[ind]=='L')ind++;
    for(int i=ind;i<a.size();i++)
    {
        if(a[i]=='L')
        {
            c+=i-ind;
            b=max(i-ind+wait++,b);
            ind++;
        }
        else
            if(wait)wait--;
    }
    cout<<b<<" "<<c;
    return 0;
}
