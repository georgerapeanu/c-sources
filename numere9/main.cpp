#include <iostream>
#include <cstdio>
using namespace std;
string cfm[]={"","unu","doi","trei","patru","cinci","sase","sapte","opt","noua"};
string cff[]={"","unu","doua","trei","patru","cinci","sase","sapte","opt","noua"};
string sg[]={"","zece","o suta","o mie","un milion","un miliard"};
string pl[]={"","zeci","sute","mii","milioane","miliarde"};
long long nr;
int T;
void afis(long long nr,bool f)
{
    if(nr>=1000000000)
    {
        if(nr/1000000000==1)
        {
            cout<<sg[5]<<" ";
            afis(nr%1000000000,0);
        }
        else if(nr<20000000000LL)
        {
            if(nr>=10000000000LL)afis(nr/1000000000,1);
            else cout<<cff[nr/1000000000]<<" ";
            cout<<pl[5]<<" ";
            afis(nr%1000000000,0);
        }
        else
        {
            afis(nr/1000000000,1);
            cout<<"de "<<pl[5]<<" ";
            afis(nr%1000000000,0);
        }
        return ;
    }
    if(nr>=1000000)
    {
        if(nr/1000000==1)
        {
            cout<<sg[4]<<" ";
            afis(nr%1000000,0);
        }
        else if(nr<20000000)
        {
            if(nr>=10000000)afis(nr/1000000,1);
            else cout<<cff[nr/1000000]<<" ";
            cout<<pl[4]<<" ";
            afis(nr%1000000,0);
        }
        else
        {
            afis(nr/1000000,1);
            cout<<"de "<<pl[4]<<" ";
            afis(nr%1000000,0);
        }
        return ;
    }
    if(nr>=1000)
    {
        if(nr/1000==1)
        {
            cout<<sg[3]<<" ";
            afis(nr%1000,0);
        }
        else if(nr<20000)
        {
            if(nr>=10000)afis(nr/1000,1);
            else cout<<cff[nr/1000]<<" ";
            cout<<(nr>=2000 ? pl[3]:sg[3])<<" ";
            afis(nr%1000,0);
        }
        else
        {
            afis(nr/1000,1);
            cout<<"de "<<pl[3]<<" ";
            afis(nr%1000,0);
        }
        return ;
    }
    if(nr>=100)
    {
        if(nr<200)cout<<sg[2]<<" ";
        else cout<<cff[nr/100]<<" "<<pl[2]<<" ";
        nr%=100;
    }
    if(nr>=10)
    {
        if(nr<20)
        {
            if(nr==10)cout<<sg[1];
            else if(nr==11)cout<<"unsprezece";
            else if(nr==14)cout<<"paisprezece";
            else if(nr==16)cout<<"saisprezece";
            else cout<<(f ? cff[nr%10]:cfm[nr%10])<<"sprezece";
            cout<<" ";
            return ;
        }
        else if(nr/10==6)cout<<"saizeci";
        else cout<<cff[nr/10]<<pl[1];
        nr%=10;
        if(nr)cout<<" si "<<(f ? cff[nr%10]:cfm[nr%10]);
        cout<<" ";
        return ;
    }
    if(nr){cout<<(f ? cff[nr%10]:cfm[nr%10]);cout<<" ";}
}
int main()
{
    freopen("numere9.in","r",stdin);
    freopen("numere9.out","w",stdout);
    cin>>T;
    while(T--)
    {
        cin>>nr;
        if(!nr){cout<<"zero\n";continue;}
        afis(nr,0);cout<<"\n";
    }
    return 0;
}
