#include <iostream>
#include <algorithm>
using namespace std;
short i, j;
char c[9][9];
short dir[65],nr;
short win;
pair <short,short> v[65];
int main()
{
    for(i=1;i<=8;i++)
    {
        for(j=1;j<=8;j++)
        {
            cin>>c[i][j];
            if(c[i][j]=='B')
            {
                dir[++nr]=1;
                v[nr].first=i;
                v[nr].second=j;
            }
            else if(c[i][j]=='W')
            {
                dir[++nr]=-1;
                v[nr].first=i;
                v[nr].second=j;
            }
        }
    }
    while(!win)
    {
        for(i=1;i<=nr;i++)
        {
            if(c[v[nr].first][v[nr].second+dir[nr]]=='.')
            {
                c[v[nr].first][v[nr].second+dir[nr]]=c[v[nr].first][v[nr].second];
                c[v[nr].first][v[nr].second]='.';
                v[nr].second+=dir[nr];
            }
            if(dir[nr]==1&&v[nr].second==8)
            {
                if(win==0)
                win=2;
            }
            if(dir[nr]==-1&&v[nr].second==1)
            {
                win=1;
            }
        }
    }
    cout<<(win==1 ? "A":"B");
    return 0;
}
