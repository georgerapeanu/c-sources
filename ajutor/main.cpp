#include <fstream>
#include <set>
using namespace std;
int i,j,k,a,b,l,x;
ofstream g("ajutor.out");
set <long long> S;
void backtracking(int nr,int st,int dr)
{
    if(nr<=7)
    {
        S.insert(dr);
        for(int i=st;i<=dr;i++)
        {
            backtracking(nr+1,dr+1,dr+i);
        }
    }
}
int main()
{
    backtracking(1,1,1);
    set<long long>::iterator it;
    for(it=S.begin();it!=S.end();it++)
        g<<*it<<" ";
    /*for(i=1;i<=9;i++)
    {
        for(j=1;j<=9;j++)
        {
            a=i*10+j;
            b=i*1000+j*110+i;
            for(k=1;k<j;k++)
            {
                a=a*a;
            }
            if(a==b)
            {
                cout<<i<<j;
            }
        }
    }*/
    /*for(i=1;i<=9;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(k=1;k<=9;k++)
            {
                a=i*100+j*10+k;
                b=i*j*j*j+6;
                if(a==b)
                {
                    cout<<i<<j<<k;
                }
            }
        }
    }*/
   /* for(i=1;i<=9;i++)
    {
        for(j=0;j<=9;j++)
        {
            for(k=0;k<=9;k++)
            {
                for(l=0;l<=9;l++)
                {
                    a=i*1000+j*100+k*10+l;
                    b=i+j+k+l;
                    if(a==((b*90)+9))
                    {
                        cout<<i<<j<<k<<l;
                    }
                }
            }
        }
    }*/
  //  a=2;
   // x+=(a%10!=0);
   // cout<<x;
    return 0;
}
