#include<iostream>
using namespace std;
int main()
{
    int h1,h2,m1,m2,h3,m3,m4,l=0,m,d,mh,hm,e=0;
    cout<<"";
    cin>>h1>>m1>>h2>>m2;
    mh=m1;
    hm=h1;
    m4=h2*60+m2;
    for(d=1;d<=m4;d++)
    {
        e=mh%5;
        if(mh==60)
        {
            hm++;
            mh=0;
        }
        m=mh/5;
        if(hm==m&&e==0)
        {
            l++;
            m4=m4-5;
        }
        mh++;
    }
    m3=m1+m2;
    h3=h1+h2;
    if(l*5>m3)
    {
        h3--;
        m3=m3+60;
        m3=m3-l*5;
    }
    else
       {m3=m3-l*5;}
       if(m3>=60)
       {
           h3++;
           m3=m3-60;
       }
    cout<<h3<<" "<<m3;
    return 0;

}
