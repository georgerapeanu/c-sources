#include <iostream>
using namespace std;
int dist[10][10];
int fr[10];
int H,W;
int main()
{
    cin>>H>>W;
    for(int i=0;i<=9;i++)
    {
        for(int j=0;j<=9;j++)
        {
            cin>>dist[i][j];
        }
    }
    for(int k=0;k<=9;k++)
        for(int i=0;i<=9;i++)
            if(i!=k)
                for(int j=0;j<=9;j++)
                    if(i!=j&&j!=k)
                        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    for(int i=1;i<=H;i++)
    {
        for(int j=1;j<=W;j++)
        {
            int val;
            cin>>val;
            if(val!=-1)fr[val]++;
        }
    }
    int rez=1<<30;
    for(int cf=1;cf<=1;cf++)
    {
        int tmp=0;
        for(int i=0;i<=9;i++)
            tmp+=dist[i][cf]*fr[i];
        rez=min(rez,tmp);
    }
    cout<<rez;
    return 0;
}
