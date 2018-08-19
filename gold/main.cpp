#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("gold.in","r");
FILE *g=fopen("gold.out","w");
typedef struct {int x,y;} POINT;
POINT A[1030];
int B[1030];
int V[1030];
int N,P,i,j;
int S,suma,st,dr;
int nr;
int a,b,c;
int orient(POINT A,POINT B,POINT C)
{
    int val=(B.y-A.y)*(C.x-B.x)-(C.y-B.y)*(B.x-A.x);
    if(val<0)
        return -1;
    if (!val)
        return 0;
    return 1;
}
bool cmp(int a,int b)
{
    if(a==i)
        return 1;
    if(b==i)
        return 0;
    if(orient(A[i],A[a],A[b])==-1)
        return 1;
    return 0;
}
int main()
{
    fscanf(f,"%d %d",&N,&P);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        B[i]=i;
        S+=V[i];
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].x,&A[i].y);
    }
    for(i=1;i<=N;i++)
    {
        sort(B+1,B+1+N,cmp);
        a=A[B[2]].y-A[i].y;
        b=A[i].x-A[B[2]].x;
        c=A[i].y*A[B[2]].x-A[i].x*A[B[2]].y;
        if(a*A[B[3]].x+b*A[B[3]].y+c<0)
        {
            dr=st=1;
            suma=V[B[3]];
           for(j=4;j<=N;j++)
           {
               if(dr==1&&(!(a*A[B[j]].x+b*A[B[j]].y+c<0)))
                    dr=j-1;
               if(a*A[B[j]].x+b*A[B[j]].y+c<0&&a*A[B[j-1]].x+b*A[B[j-1]].y+c>=0)
                    st=j;
                if(a*A[B[j]].x+b*A[B[j]].y+c<0)
                    suma+=V[B[j]];
           }
           if(dr==1)
                {st=3;dr=N;}
            else if(st==1)
                st=3;
        }
        else
        {
            st=dr=1;
            for(j=4;j<=N;j++)
           {
               if(st==1&&(a*A[B[j]].x+b*A[B[j]].y+c<0))
                    st=j;
               if(a*A[B[j]].x+b*A[B[j]].y+c<0)
                    dr=j;
                if(a*A[B[j]].x+b*A[B[j]].y+c<0)
                    suma+=V[B[j]];
           }
           if(dr==1)
           {
               st=1;
               dr=N;
           }
        }
        if(abs(S-suma-V[i]-V[B[2]]-suma)<=P)
            nr++;
        for(j=3;j<=N;j++)
        {
            a=A[B[j]].y-A[i].y;
            b=A[i].x-A[B[j]].x;
            c=A[i].y*A[B[j]].x-A[i].x*A[B[j]].y;
            while(dr!=st&&a*A[B[dr]].x+b*A[B[dr]].y+c<0)
            {
                dr++;
                if(dr==N+1)
                    dr=2;
                suma+=V[B[dr]];
            }
            suma-=V[B[dr]];
            if(dr==2)
                dr=N+1;
            dr--;
            ///-> problem 6 2
            while(st!=dr&&a*A[B[st]].x+b*A[B[st]].y+c>=0)
            {
                suma-=V[B[st]];
                st++;
                if(st==N+1)
                    st=2;
            }
            if(abs(S-suma-V[i]-V[B[j]]-suma)<=P)
                nr++;
        }
    }
    fprintf(g,"%d",nr/2);
    fclose(f);
    fclose(g);
    return 0;
}
