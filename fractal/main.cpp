#include <cstdio>
#include <algorithm>
using namespace std;
typedef struct {int x,y;} punct;
FILE *f=fopen("fractal.in","r");
FILE *g=fopen("fractal.out","w");
int k,x,y,p,val;
punct mid,rel;
typedef struct{double x,y;} PUNCT;
PUNCT S,D,M,R;
int rez(punct st,punct dr)
{
    if(dr.x-st.x<=1)
        {S={st.x,st.y};D={dr.x,dr.y};return 0;}
                mid={(st.x+dr.x)/2,(st.y+dr.y)/2};
    rel={mid.x-x,mid.y-y};
     dr={dr.x-st.x+1,dr.y-st.y+1};
    st={1,1};        mid={(st.x+dr.x)/2,(st.y+dr.y)/2};
    if(p==1)
    {
        rel={-rel.y+mid.x,-rel.x+mid.y};
    }
    else if(p==2)
    {
       x-=mid.x;
    }
    else if(p==3)
    {
        y-=mid.y;
    }
    else if(p==4)
    {
        rel={rel.y+mid.x,rel.x+mid.y};
    }
    if(p)
    {x=rel.x;
    y=rel.y; }
    if(x<=mid.x&&y<=mid.y)
        {p=1;return rez(st,mid);}
    if(x<=mid.x&&y>mid.y)
        {p=4;return 3*(mid.x-st.x+1)*(mid.x-st.x+1)+rez({st.x,mid.y+1},{mid.x,dr.y});}
    if(x>mid.x&&y<=mid.y)
        {p=2;return (mid.x-st.x+1)*(mid.x-st.x+1)+rez({mid.x+1,st.y},{dr.x,mid.y});}
    if(x>mid.x&&y>mid.y)
        {p=3;return 2*(mid.x-st.x+1)*(mid.x-st.x+1)+rez({mid.x+1,mid.y+1},dr);}
}
int main()
{
    fscanf(f,"%d %d %d",&k,&x,&y);
    swap(x,y);
    val=rez({1,1},{1<<k,1<<k});
    M={(S.x+D.x)/2,(S.y+D.y)/2};
    R={M.x-x,M.y-y};
    M={1.5,1.5};
    if(p==1)
    {
        R={-R.y+M.x,-R.x+M.y};
    }
    else if(p==2)
    {
       x-=M.x;
    }
    else if(p==3)
    {
        y-=M.y;
    }
    else if(p==4)
    {
        R={R.y+M.x,R.x+M.y};
    }
    if(p)
    {x=R.x;
    y=R.y;}
    if(x==1&&y==1)
        ;
    else if(x==2&&y==1)
        val++;
    else if(x==2&&y==2)
        val+=2;
    else
        val+=3;
    fprintf(g,"%d",val);
    fclose(f);
    fclose(g);
    return 0;
}
