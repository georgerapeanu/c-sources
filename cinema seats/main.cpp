#include <iostream>
#include <vector>
using namespace std;
string a;
vector<int> nr;
int tmp;
int rez;
int V[100005];
int l,r;
int main() {
    cin>>a;
    l=0;r=-1;
    V[0]=(a[0]=='0');
    for(int i=1;i<a.size();i++)
    {
        V[i]=V[i-1]+(a[i]=='0');
    }
    for(int i=0;i<a.size();i++)
    {
        int st,dr;
        st=i;
        dr=a.size()-1;
        while(st<dr)
        {
            int mid=(1+st+dr)/2;
            if(V[mid]-V[i-1]>=mid-i)
            {
                st=mid;
            }
            else
            {
                dr=mid-1;
            }
        }
        if(V[st]-V[i-1]==V[a.size()-1])
        {
            rez=max(rez,st-i);
        }
        else
        {
            rez=max(rez,st-i+1);
        }
    }
    cout<<rez;
    return 0;
}
