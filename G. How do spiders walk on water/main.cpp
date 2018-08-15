#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
char C[30000000];
long long D,P,N;
long long ind=0;
long long tmp;
long long S[10005];
int i32()
{
    while(C[ind]<'0'||C[ind]>'9')
    {
        if(C[ind]=='\0')return -1;
        ind++;
    }
    long long nr=0;
    while(C[ind]>='0'&&C[ind]<='9')
    {
        nr=10*nr+(C[ind]-'0');
        ind++;
    }
    return nr;
}
int main()
{
    ///freopen("in","r",stdin);
    ///freopen("out","w",stdout);
    while(cin.getline(C,30000000))
    {
        ind =0;
        D=i32();if(D==-1)break;
        P=i32();
        N=0;
        do
        {
            tmp=i32();
            if(tmp==-1)break;
            S[++N]=tmp;
        }
        while(1);
        if(N<D+1)
        {
            if(S[2]==0)
            {
                while(N<=D)
                {
                    S[++N]=0;
                }
            }
            else
            {
                if(S[4]>P)
                {
                    for(N=4;N<=D+1;N++)
                        S[N]=P+1;
                    N--;
                }
                else
                {
                    if(S[1]*S[3]==S[2]*S[2])
                    {
                        for(;N<=D+1;N++)
                        {
                            S[N]=S[N-1]*S[3]/S[2];
                            if(S[N]>P)
                                S[N]=P+1;
                        }
                        N--;
                    }
                    else
                    {
                        long long x=S[2]*S[4]-S[3]*S[3];
                        long long q=S[2]*S[2]-S[1]*S[3];
                        long long y=S[3]*S[2]-S[1]*S[4];
                        x/=q;
                        y/=q;
                        for(;N<=D+1;N++)
                        {
                            S[N]=S[N-2]*x+S[N-1]*y;
                            if(S[N]>P)
                                S[N]=P+1;
                        }
                        N--;
                    }
                }
            }
        }
        if(S[1]>P)
            cout<<"The spider is going to fall!\n";
        else if(S[D+1]<=P)
            cout<<"The spider may fall!\n";
        else
        {
            int poz=1;
            while(S[poz+1]<=P&&poz<=D)
                poz++;
            cout<<D+1-poz<<"\n";
        }
    }
    return 0;
}
