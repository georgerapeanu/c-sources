#include <iostream>
using namespace std;
int n,x[5],y[5],i,arie,j;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>x[i]>>y[i];
    }
    if(n>=3)
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(i!=j)
                {
                    if(x[i]!=x[j]&&y[i]!=y[j])
                    {
                          arie=(x[i]-x[j])*(y[i]-y[j]);
                        if(arie<0)
                        arie*=-1;
                        i=n;
                        j=n;
                    }
                }
            }
        }
        cout<<arie;
    }
    else if(n==2)
    {
        if(x[1]!=x[2]&&y[1]!=y[2])
        {
            arie=(x[1]-x[2])*(y[1]-y[2]);
            if(arie<0)
            arie*=-1;
            cout<<arie;
        }
        else
        cout<<-1;
    }
    else
    {
        cout<<-1;
    }
    return 0;
}
