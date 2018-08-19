#include <iostream>
#include <algorithm>
using namespace std;
int N;
typedef struct{int x,y,nr;} segment;
segment V[505];
segment L[505];
int P[505];
vector<int> rez;
int nr=0;
bool cmp(segment a,segment b)
{
        if(a.y!=b.y)
                return a.y<b.y;
        return a.x<b.x;
}
int main()
{
        cin>>N;
        for(int i=1;i<=N;i++)
        {
                cin>>V[i].x>>V[i].y;
                V[i].nr=i;
        }
        sort(V+1,V+1+N,cmp);
        for(int i=1;i<=N;i++)
        {
                int st=1,dr=nr,last=0,mid;
                while(st<=dr)
                {
                        mid=(st+dr)/2;
                        if(L[mid].y<V[i].y&&L[mid].x>V[i].x)
                        {
                                last=mid;
                                st=mid+1;
                        }
                        else
                                dr=mid-1;
                }
                if(last==nr)
                {
                    L[++nr]=V[i];
                }
                else if(L[last+1].x<V[i].x)
                        L[last+1]=V[i];
                P[V[i].nr]=L[last].nr;
        }
        cout<<nr<<'\n';
        int aux=L[nr].nr;
        while(aux)
        {
            rez.push_back(aux);
            aux=P[aux];
        }
        for(vector <int> ::reverse_iterator it=rez.rbegin();it!=rez.rend();it++)
            cout<<*it<<" ";
        return 0;
}
