#include <iostream>

using namespace std;
FILE *f=fopen("treap.in","r");
FILE *g=fopen("treap.out","w");
pair<int,int> dfs(int nod,int tata)
{
    pair<int,int> rez={1,1};
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            pair<int,int> tmp=dfs(it);
            rez.first&=(tmp.first&&P[nod]>=P[it]);
        }
    }
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
