#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int sz;
int op;
int N;
char C[]="IARD";
int main()
{
    srand(time(NULL));
    N=rand()%300;
    freopen("secv8.in","w",stdout);
    cout<<N<<" 1\n";
    for(int i=1;i<=N;i++)
    {
        if(sz==0)
        {
            cout<<C[0]<<" "<<1<<" "<<rand()%10000<<"\n";
            sz++;
        }
        else
        {
            op=rand()%4;
            if(op==0){cout<<C[0]<<" "<<rand()%(sz+1)+1<<" "<<rand()%10000<<"\n";sz++;}
            else if(op==1)cout<<C[1]<<" "<<rand()%sz+1<<"\n";
            else if(op==2)
            {
                int x,y;
                x=rand()%sz+1;
                y=rand()%sz+1;
                if(x>y)swap(x,y);
                cout<<C[2]<<" "<<x<<" "<<y<<"\n";
            }
            else
            {
                int x,y;
                x=rand()%sz+1;
                y=rand()%sz+1;
                if(x>y)swap(x,y);
                cout<<C[3]<<" "<<x<<" "<<y<<"\n";
                sz-=(y-x+1);
            }
        }
    }
    return 0;
}
