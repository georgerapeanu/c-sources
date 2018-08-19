#include <fstream>
#include <queue>
#include <>
using namespace std;
queue <int> Qx,Qy;
void copiere(int x,int y,int xx,int yy)
{
    for(std::vector<point>::iterator it=D[x][y].begin();it!=D[x][y].end();it++)
    {
        D[xx][yy].push_back(*it);
    }
}

void Lee(int x,int y)
{
    Qx.push(x);
    Qy.push(y);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(int i=0;i<4;i++)
        {
            int xx,yy;
            xx=x+dirx[i];
            yy=y+diry[i];
            if(xx&&yy&&xx<=n&&yy<=n)
            {
                if(A[xx][yy]==0)
                {
                    A[xx][yy]=A[x][y]+1;
                    copiere(x,y,xx,yy);
                    D[xx][yy].push_back(point(x,y));
                    Qx.push(xx);
                    Qy.push(yy);
                }
            }
        }
    }
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
