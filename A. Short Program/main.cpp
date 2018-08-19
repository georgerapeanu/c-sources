#include <iostream>
using namespace std;
int V[13];
int N;
int main()
{
    for(int i=0;i<10;i++)V[i]=2;
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        char c;
        int val;
        cin>>c>>val;
        if(c=='&')
        {
            for(int j=0;j<10;j++)
            {
                if((val>>j)&1)
                {
                        ;
                }
                else
                {
                    V[j]=0;
                }
            }
        }
        else if(c=='|')
        {
            for(int j=0;j<10;j++)
            {
                if((val>>j)&1)
                {
                   V[j]=1;
                }
            }
        }
        else
        {
            for(int j=0;j<10;j++)
            {
                if((val>>j)&1)
                {
                   V[j]^=1;
                }
            }
        }
    }
    cout<<"3\n";
    int nr=0;
    for(int i=0;i<10;i++)
    {
        if(V[i]==1)
        {
            nr|=(1<<i);
        }
    }
    cout<<"| "<<nr<<"\n";
    nr=0;
    for(int i=0;i<10;i++)
    {
        if(V[i]!=0)
        {
            nr|=(1<<i);
        }
    }
    cout<<"& "<<nr<<"\n";
    nr=0;
    for(int i=0;i<10;i++)
    {
        if(V[i]==3)
        {
            nr|=(1<<i);
        }
    }
    cout<<"^ "<<nr<<"\n";
    return 0;
}
