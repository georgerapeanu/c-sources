#include <iostream>
#include <algorithm>
using namespace std;
int val;
int N,maxim,maximimpar;
int rez=0;
int inclus,exclus;
int main()
{
    cin>>N;
    inclus=(1<<30);exclus=(-(1<<30));
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        maxim=max(maxim,val);
        if(val%2==1)maximimpar=max(maximimpar,val);
        if(val<=0)
        {
            if(val%2)exclus=max(val,exclus);
        }
        else
        {
            rez+=val;
            if(val%2)inclus=min(inclus,val);
        }
    }
    if(rez%2==0)
    {
        if(inclus!=(1<<30)&&exclus==(-(1<<30)))
        {
            rez-=inclus;
        }
        else if(inclus==(1<<30)&&exclus!=(-(1<<30)))
        {
            rez+=exclus;
        }
        else
        {
            rez=max(rez-inclus,rez+exclus);
        }
    }
    if(maxim<0)cout<<maximimpar;
    else  cout<<rez;
    return 0;
}
