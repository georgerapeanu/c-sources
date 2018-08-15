#include <iostream>
#include <vector>
#define st first
#define dr second
using namespace std;
vector<pair<int,int> > V;
int A[105],N;
bool ok=0;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        ok=ok|(A[i]!=0);
    }
    if(!ok)
    {
        cout<<"NO";return 0;
    }
    for(int i=1;i<=N;i++)
    {
        int x=i,y=0;
        while(A[i]==0)
            i++;
        if(i<N&&A[i+1]==0)
        {
            i++;
            while(i<N&&A[i+1]==0)
                i++;
            y=i;
        }
        else
        {
            y=i;
        }
        V.push_back(make_pair(x,y));
    }
    cout<<"YES\n";
    cout<<V.size()<<"\n";
    for(auto it:V)
        cout<<it.st<<" "<<it.dr<<"\n";
    return 0;
}
