#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <iomanip>
#define PI 3.14159265358979323846
using namespace std;
typedef struct{double x,y;} punct; //a point
punct P,varf[100000];
int N,i;
double rez,R,r;
double dist(punct A,punct B) //distance between 2 points A and B
{
    return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}
double intersectie(punct A,punct B,punct M)
{
    double x=0,y=0,mMO=0,mAB=0;
    mAB=(B.y-A.y)/(B.x-A.x); //m from the straight line equation for side
    if(mAB!=0)
    {
    mMO=(A.x-B.x)/(B.y-A.y); //m for the distance from M to AB
    x=(mMO*M.x-mAB*A.x+A.y-M.y)/(mMO-mAB);  // after equations solved, that's the x for O(the end of the perpendicular segment)
    y=mMO*(x-M.x)+M.y; //y for point O
    }
    else
    {
        x=M.x;
        y=A.y;
    }
    punct O;//the point O
    O.x=x;
    O.y=y;
    if((A.x<=x&&x<=B.x)||(A.x>=x&&x>=B.x))//if O is on AB
        return dist(O,M);
    else
        return min(dist(M,A),dist(M,B));
}
int main()
{
    cin>>N>>P.x>>P.y;
    for(i=1;i<=N;i++)
    {
        cin>>varf[i].x>>varf[i].y; //reading
    }
    r=90000000000000; //min distance to a side of the poligon
    for(i=1;i<=N;i++)
    {
        R=max(R,dist(P,varf[i])); //max distance from P to vertices
        r=min(r,intersectie(varf[i],varf[i%N+1],P));
    }
    rez=PI*pow(R,2)-PI*pow(r,2); //area of big circle - area of little circle
    cout<<setprecision(20)<<rez; //printing the result with precision of 20
    return 0;
}
