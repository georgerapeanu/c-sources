#include <cstdio>
using namespace std;
FILE *f=fopen("poligon2.in","r");
FILE *g=fopen("poligon2.out","w");
int N;
struct point{double x,y;};
point P[10005];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lf %lf",&P[i].x,&P[i].y);
    }
    if(N%2==0)
    {
        point rez={0,0};
        for(int i=N;i;i-=2)
        {
            rez.x+=P[i].x-P[i-1].x;
            rez.y+=P[i].y-P[i-1].y;
        }
        if(rez.x||rez.y)
        {
            fprintf(g,"fara solutie");
            return 0;
        }
        else
        {
            point st={-1,1};
            for(int i=1;i<=N;i++)
            {
                fprintf(g,"%.3f %.3f\n",st.x,st.y);
                st.x=2*P[i].x-st.x;
                st.y=2*P[i].y-st.y;
            }
            ///fprintf(g,"%.3f %.3f\n",st.x,st.y);
        }
    }
    else
    {
        point rez={P[N].x,P[N].y};
        for(int i=N-1;i;i-=2)
        {
            rez.x+=P[i-1].x-P[i].x;
            rez.y+=P[i-1].y-P[i].y;
        }
        for(int i=1;i<=N;i++)
        {
            fprintf(g,"%.3f %.3f\n",rez.x,rez.y);
            rez.x=2*P[i].x-rez.x;
            rez.y=2*P[i].y-rez.y;
        }
        ///fprintf(g,"%.3f %.3f\n",rez.x,rez.y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
