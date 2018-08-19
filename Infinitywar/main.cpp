#include <cstdio>
#include <algorithm>
#define rad 230
#define x first.first
#define y first.second
#define ind second
using namespace std;
FILE *f=fopen("infinitywar.in","r");
FILE *g=fopen("infinitywar.out","w");
int N,Q;
int V[300005];
pair<pair<int,int>,int> A[100005];
int st[50005];
int dr[50005];
const int LEN=10000000;
int ind=LEN-1;
char buff[LEN];
int rez[100005];
bool B[10005];
int tmp=0;
int i32()
{
    int val=0;
    while(buff[ind]<'0'||buff[ind]>'9'){
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        val=10*val+buff[ind]-'0';
        if(++ind>=LEN){
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return val;
}
bool cmp(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.x/rad!=b.x/rad)return a.x<b.x;
    return a.y<b.y;
}
void op(int pos)
{
    for(int i=st[pos];i<=dr[pos];i++)
    {
        if(B[V[i]])
        {
            tmp--;
        }
        else
        {
            tmp++;
        }
        B[V[i]]^=1;
    }
}
int main()
{
    N=i32();Q=i32();
    for(int i=1;i<=N;i++)
    {
        int K=i32();
        st[i]=dr[i-1]+1;
        dr[i]=st[i]-1;
        for(int j=1;j<=K;j++)
        {
            V[++dr[i]]=i32();
        }
    }
    for(int i=1;i<=Q;i++)
    {
        A[i].x=i32();
        A[i].y=i32();
        A[i].ind=i;
    }
    sort(A+1,A+1+Q,cmp);
    int l=1,r=0;
    for(int i=1;i<=Q;i++)
    {
        while(l<A[i].x)op(l++);
        while(r<A[i].y)op(++r);
        while(l>A[i].x)op(--l);
        while(r>A[i].y)op(r--);
        rez[A[i].ind]=tmp;
    }
    for(int i=1;i<=Q;i++)fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
