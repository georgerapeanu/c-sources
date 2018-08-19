#include<iostream>
#include<fstream>
using namespace std;
ifstream f("alice.in");
ofstream g("alice.out");
int main()
{
    int N,K,p,u,m=0,pp,z,upp,i,mpp,j,l=0,uj,c=0;
    //a)
    f>>N;
    f>>K;
    for(u=1;u<=N;u++)
    {
        f>>p;
        pp=p;
        if(p%2==0)
        {
            if(p>m)
                m=p;
        }
        i=1;
        z=0;
        while(z!=1 or i<=100)
        {
            mpp=0;
            j=0;
            while(pp!=0)
            {
                upp=pp%10;
                pp=pp/10;
                if(upp>mpp)
                    mpp=pp;
                while(p!=0)
                {
                    upp=p%10;
                    j=j*10+mpp-upp;
                    p=p/10;cout<<j<<endl;
                }
                while(j!=0)
                {
                    uj=j%10;
                    l=l*10+uj;
                    j=j/10;z++;cout<<l<<endl;
                }
            }
            i++;
        }
        if(l==K)
            c++;
    }
    g<<m<<endl;
    g<<c;
    f.close();g.close();
    return 0;
}
