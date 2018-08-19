#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#define x first
#define pb push_back
#define mp make_pair
#define EPS 0.000000001
#define y second
using namespace std;
FILE *f=fopen("nori.in","r");
FILE *g=fopen("nori.out","w");
int N,M;
bool ok;
int X,Y,R;
vector<pair<double,double> > inte;
vector<pair<double,double> > Rinte;
double dist(double X,double Y)
{
    return sqrt(pow(X,2)+pow(Y,2));
}
void ins(int X,int Y,int R)
{
    double teta,alfa;
    teta=atan2(Y,X);
    alfa=asin(R/dist(X,Y));
    inte.pb(mp(teta-alfa,teta+alfa));
}
bool q(int X,int Y)
{
    double m=atan2(Y,X);
    int st=0,dr=Rinte.size()-1;
    while(st<=dr)
    {
        int mid=(st+dr)/2;
        if(m-Rinte[mid].y<=EPS&&Rinte[mid].x-m<=EPS)
        {
            return 0;
        }
        if(m-Rinte[mid].y>EPS)
            st=mid+1;
        else
            dr=mid-1;
    }
    return 1;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        int X,Y,R;
        fscanf(f,"%d%d%d",&X,&Y,&R);
        ins(X,Y,R);
    }
    sort(inte.begin(),inte.end());
    Rinte.pb(inte[0]);
    for(int i=1;i<inte.size();i++)
    {
        if(Rinte[Rinte.size()-1].y>inte[i].y) continue;
        if(Rinte[Rinte.size()-1].y<inte[i].x) Rinte.pb(inte[i]);
        else Rinte[Rinte.size()-1].y=inte[i].y;
    }
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&X,&Y);
        fprintf(g,"%d",q(X,Y));
    }
    fclose(f);
    fclose(g);
    return 0;
}
