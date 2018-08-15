#include <iostream>
using namespace std;
string a;
int fr[5005][2];
int rez;
int make(int st,int dr,char a)
{
    if(dr<st)return 0;
    return (dr-st+1)-(fr[dr][a-'a']-(st!=0 ? fr[st-1][a-'a']:0));
}
int main()
{
    cin>>a;
    for(int i=0;i<a.size();i++)
    {
        fr[i][a[i]-'a']++;
        if(i)
        {
            fr[i][0]+=fr[i-1][0];
            fr[i][1]+=fr[i-1][1];
        }
    }
    for(int i=-1;i<(int)a.size();i++)
    {
        for(int j=i;j<(int)a.size();j++)
        {
            rez=max(rez,(int)(a.size()-make(0,i,'a')-make(i+1,j,'b')-make(j+1,a.size()-1,'a')));
        }
    }
    cout<<rez;
    return 0;
}
