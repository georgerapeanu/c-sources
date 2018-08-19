#include <cstdio>
#include <algorithm>
#define NMAX 100005
#define LL unsigned long long
using namespace std;
FILE *f=fopen("cmap.in","r");
FILE *g=fopen("cmap.out","w");
typedef pair<LL,LL> point;
vector <point> V(NMAX);
vector<point> X,Y;
int N;
LL dist(point a,point b)
{
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}
LL getmin(int st,int dr)///st...dr-1
{
    if(st>=dr-1)
        return (1LL<<63);
    if(st==dr-2)
    {
        if(Y[dr-1]<Y[st])
            swap(Y[st],Y[dr-1]);
        return dist(Y[st],Y[dr-1]);
    }
    int mid=(st+dr)/2;
    LL minim=min(getmin(st,mid),getmin(mid,dr));
    merge(Y.begin()+st,Y.begin()+mid,Y.begin()+mid,Y.begin()+dr,V.begin());
    copy(V.begin(),V.begin()+(dr-st),Y.begin()+st);
    int ind=0;
    for(int i=st;i<dr;i++)
        if(abs(Y[i].second-X[mid].first)<=minim)
            V[ind++]=Y[i];
    for(int i=0;i<ind;i++)
        for(int j=i+1;j<ind&&j-i<=7;j++)
            minim=min(minim,dist(V[j],V[i]));
    return minim;
}
int main()
{
    fscanf(f,"%d",&N);
    X.resize(N);
    Y.resize(N);
    for(int i=0;i<N;i++)
        fscanf(f,"%d%d",&X[i].first,&X[i].second);
    sort(X.begin(),X.end());
    for(int i=0;i<N;i++)
        Y[i]=make_pair(X[i].second,X[i].first);
    double val=sqrt(double(getmin(0,N)));
    fprintf(g,"%.6f",val);
    fclose(f);
    fclose(g);
    return 0;
}
