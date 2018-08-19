#include <iostream>
#include <queue>
using namespace std;
bool viz[256][256][256];
bool V[1000];
typedef struct {int v1,v2,v3;} obiect;
queue<obiect> Q;
obiect A,B;
int val,nr;
int main()
{
    cin>>A.v1>>A.v2>>A.v3;
    Q.push({0,0,0});
    viz[0][0][0]=1;
    while(!Q.empty())
    {
        B=Q.front();
        Q.pop();
        V[B.v1+B.v2+B.v3]=1;
        V[B.v1+B.v2]=1;
        V[B.v3+B.v2]=1;
        V[B.v3+B.v1]=1;
        V[B.v1]=1;
        V[B.v2]=1;
        V[B.v3]=1;
        if(!viz[A.v1][B.v2][B.v3])
        {
            viz[A.v1][B.v2][B.v3]=1;
            Q.push({A.v1,B.v2,B.v3});
        }
        if(!viz[B.v1][A.v2][B.v3])
        {
            viz[B.v1][A.v2][B.v3]=1;
            Q.push({B.v1,A.v2,B.v3});
        }
        if(!viz[B.v1][B.v2][A.v3])
        {
            viz[B.v1][B.v2][A.v3]=1;
            Q.push({B.v1,B.v2,A.v3});
        }
        val=min(A.v1-B.v1,B.v2);
        if(!viz[B.v1+val][B.v2-val][B.v3])
        {
            viz[B.v1+val][B.v2-val][B.v3]=1;
            Q.push({B.v1+val,B.v2-val,B.v3});
        }
        val=min(A.v1-B.v1,B.v3);
        if(!viz[B.v1+val][B.v2][B.v3-val])
        {
            viz[B.v1+val][B.v2][B.v3-val]=1;
            Q.push({B.v1+val,B.v2,B.v3-val});
        }
        val=min(A.v2-B.v2,B.v1);
        if(!viz[B.v1-val][B.v2+val][B.v3])
        {
            viz[B.v1-val][B.v2+val][B.v3]=1;
            Q.push({B.v1-val,B.v2+val,B.v3});
        }
        val=min(A.v2-B.v2,B.v3);
        if(!viz[B.v1][B.v2+val][B.v3-val])
        {
            viz[B.v1][B.v2+val][B.v3-val]=1;
            Q.push({B.v1,B.v2+val,B.v3-val});
        }
        val=min(A.v3-B.v3,B.v1);
        if(!viz[B.v1-val][B.v2][B.v3+val])
        {
            viz[B.v1-val][B.v2][B.v3+val]=1;
            Q.push({B.v1-val,B.v2,B.v3+val});
        }
        val=min(A.v3-B.v3,B.v2);
        if(!viz[B.v1][B.v2-val][B.v3+val])
        {
            viz[B.v1][B.v2-val][B.v3+val]=1;
            Q.push({B.v1,B.v2-val,B.v3+val});
        }

    }
    for(int i=1;i<1000;i++)
        nr+=V[i];
    cout<<nr;
    return 0;
}
