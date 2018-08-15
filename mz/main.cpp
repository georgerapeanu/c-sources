#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#define x first
#define y second
using namespace std;
FILE *f=fopen("mz.in","r");
FILE *g=fopen("mz.out","w");
int dim;
int nr[1000005];
int V[1005][1005];
int ant[1005][1005];
int nrvec[1005][1005];
char C[1005][1005];
int N,M;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int maxim;
int m1,m2,t1,t2;
pair<int,int> c1,c2;
void fi(int x,int y,char v,int val)
{
    queue<int> Qx,Qy;
    Qx.push(x);
    Qy.push(y);
    V[x][y]=val;
    m1=m2=t1=t2=0;
    while(!Qx.empty())
    {
        x=Qx.front();Qx.pop();
        y=Qy.front();Qy.pop();
        if(val>0)nr[val]++;
        for(int k=0;k<4;k++)
        {
            int nx=x+dx[k];
            int ny=y+dy[k];
            if(nx&&ny&&nx<=N&&ny<=M)
            {
                if(((!V[nx][ny]&&val!=-2)||(V[nx][ny]==-1&&val==-2))&&C[nx][ny]==v)
                {
                    V[nx][ny]=val;
                    ant[nx][ny]=k;
                    nrvec[x][y]++;
                    nrvec[nx][ny]++;
                    Qx.push(nx);
                    Qy.push(ny);
                }
                if(V[nx][ny]>0&&val==-1)
                {
                    if(nrvec[nx][ny]<=1)
                    {
                        if(t1==V[nx][ny]||t2==V[nx][ny])continue;
                        if(nr[V[nx][ny]]>=m1)
                        {
                            m2=m1;t2=t1;c2=c1;
                            t1=V[nx][ny];
                            m1=nr[V[nx][ny]];
                            c1={nx,ny};
                        }
                        else if(nr[V[nx][ny]]>m2)
                        {
                            m2=nr[V[nx][ny]];
                            t2=V[nx][ny];
                            c2={nx,ny};
                        }
                    }
                }
            }
        }
    }

}
pair<int,int> st,dr;
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fgets(C[i]+1,1005,f);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(!V[i][j]&&C[i][j]!='0')fi(i,j,C[i][j],++dim);
        }
    }
    fprintf(g,"%d\n",dim);
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(C[i][j]=='0'&&V[i][j]!=-1)
            {
                fi(i,j,C[i][j],-1);
                if(m1&&m2)
                {
                    if(rez<m1+m2)
                    {
                        rez=m1+m2;
                        st=c1;
                        dr=c2;
                    }
                }
            }
        }
    }
    fprintf(g,"%d\n",rez);
    char a=C[st.first][st.second],b=C[dr.first][dr.second];
    V[st.first][st.second]=-1;
    C[st.first][st.second]='0';
    V[dr.first][dr.second]=-1;
    C[dr.first][dr.second]='0';
    fi(st.first,st.second,'0',-2);
    C[st.first][st.second]=a;
    C[dr.first][dr.second]=b;
    pair<int,int> tmp=dr;
    while(st!=dr)
    {
        int k=ant[tmp.x][tmp.y];
        tmp.x-=dx[k];
        tmp.y-=dy[k];
        if(tmp==st)break;
        C[tmp.x][tmp.y]='x';
    }
    for(int i=1;i<=N;i++)
    {
        fputs(C[i]+1,g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
