#include <cstdio>
#include <iostream>
#include <deque>
using namespace std;
FILE *f=fopen("tdeque.in","r");
deque<int> D;
int N;
int val;
int minim=1005;
string a;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        if(minim>val)
        {
            int nr=0;
            while(minim!=1005&&D.back()!=minim)
            {
                D.push_front(D.back());
                D.pop_back();
                nr++;
            }
            if(minim!=1005)
            {
                D.push_front(D.back());
                D.pop_back();
                nr++;
            }
            if(nr>D.size()/2)
            {
                nr=D.size()-nr;
                for(int j=1;j<=nr;j++)
                    a.push_back('3');
                a.push_back('1');
            }
            else
            {
                for(int j=1;j<=nr;j++)
                    a.push_back('2');
                a.push_back('1');
            }
            minim=val;
        }
        else
        {
            int nr=0,maxim=0,rnr=0;
            for(int j=D.size();j;j--)
            {
                if(maxim<D.back()&&D.back()<val)
                {
                    rnr=nr;
                    maxim=D.back();
                }
                nr++;
                D.push_front(D.back());
                D.pop_back();
            }
            if(rnr>D.size()/2)
            {
                rnr=D.size()-rnr;
                for(int j=1;j<=rnr;j++)
                    {a.push_back('3');D.push_back(D.front());D.pop_front();}
                a.push_back('1');
            }
            else
            {
                for(int j=1;j<=rnr;j++)
                    {a.push_back('2');D.push_front(D.back());D.pop_back();}
                a.push_back('1');
            }
        }
        D.push_back(val);
    }
    int nr=0;
    while(D.back()!=N)
    {
        D.push_front(D.back());
        D.pop_back();
        nr++;
    }
    if(nr>N/2)
    {
        nr=N-nr;
        for(int i=1;i<=nr;i++)
            a.push_back('3');
    }
    else
    {
        for(int i=1;i<=nr;i++)
            a.push_back('2');
    }
    freopen("tdeque.out","w",stdout);
    cout<<a.size()<<"\n"<<a;
    fclose(f);
    return 0;
}
