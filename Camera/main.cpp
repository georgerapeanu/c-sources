#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
FILE *f=fopen("camera.in","r");
FILE *g=fopen("camera.out","w");
struct punct
{
    double x,y;
    punct()
    {
        ;
    }
    punct(double X,double Y)
    {
        x=X;
        y=Y;
    }
    bool operator < (const punct &other)const
    {
        if(x!=other.x)return x<other.x;
        return y<other.y;
    }
};
struct dreapta
{
    double a,b,c;
    dreapta()
    {
        ;
    }
    dreapta(punct P1,punct P2)
    {
        a=P2.y-P1.y;
        b=P1.x-P2.x;
        c=P2.x*P1.y-P1.x*P2.y;
    }
    punct n(dreapta other)
    {
        punct rez;
        rez.y=(c*other.a-other.c*a)/(other.b*a-b*other.a);
        rez.x=(-c*other.b+other.c*b)/(other.b*a-b*other.a);
        return rez;
    }
};
double det(punct p1,punct p2,punct p3)
{
    return p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p3.x*p2.y-p1.x*p3.y-p2.x*p1.y;
}
int sign(double x)
{
    if(-1e-6<x&&x<1e-6)return 0;
    if(x>0)return 1;
    return -1;
}
int N,M=4;
punct V[2005];
punct P[6005];
punct tmp[6005];
int main()
{
    P[1]={1e5,1e5};
    P[2]={-1e5,1e5};
    P[3]={-1e5,-1e5};
    P[4]={1e5,-1e5};
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lf %lf",&V[i].x,&V[i].y);
        P[1].x=min(P[1].x,V[i].x);P[1].y=min(P[1].y,V[i].y);
        P[2].x=max(P[2].x,V[i].x);P[2].y=min(P[2].y,V[i].y);
        P[3].x=max(P[3].x,V[i].x);P[3].y=max(P[3].y,V[i].y);
        P[4].x=min(P[4].x,V[i].x);P[4].y=max(P[4].y,V[i].y);
    }
    double area=0;for(int i=1;i<=N;i++)area+=det({0,0},V[i],V[i%N+1]);
    if(area<0)reverse(V+1,V+1+N);
    V[N+1]=V[1];P[M+1]=P[1];
    for(int i=1;i<=N;i++)
    {
        int ind=0;
        punct p1=V[i],p2=V[i+1];
        for(int j=1;j<=M;j++)
        {
            punct p3=P[j];
            punct p4=P[j+1];
            if(sign(det(p1,p2,p3))*sign(det(p1,p2,p4))<0)
            {
                if(sign(det(p1,p2,p4))>0)
                {
                    tmp[++ind]=dreapta(p1,p2).n(dreapta(p3,p4));
                    tmp[++ind]=p4;
                }
                else
                {
                    tmp[++ind]=dreapta(p1,p2).n(dreapta(p3,p4));
                }
            }
            else
            {
                if(sign(det(p1,p2,p4))>=0)
                {
                    tmp[++ind]=p4;
                }
            }
        }
        M=ind;
        memcpy(P,tmp,sizeof(tmp));
        memset(tmp,0,sizeof(tmp));
        P[M+1]=P[1];
        ///for(int i=1;i<=M;i++)cerr<<P[i].x<<" "<<P[i].y<<"\n";cerr<<"\n\n";
    }
    area=0;for(int i=1;i<=M;i++)area+=det({0,0},P[i],P[i+1]);
    fprintf(g,"%.2f",abs(area)/2);
    fclose(f);
    fclose(g);
    return 0;
}
