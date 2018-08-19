#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int fr[100006];
int N,M,H,W;
vector<int> T;
long long rez;
int main() {
    cin>>H>>W>>N>>M;
    T.push_back(0);
    for(int i=1;i<=N;i++)
    {
        int x;
        cin>>x;
        T.push_back(x);
    }
    T.push_back(H);
    sort(T.begin(),T.end());
    for(int i=1;i<T.size();i++)
    {
        fr[T[i]-T[i-1]]++;
    }
    T.clear();
    T.push_back(0);
    for(int i=1;i<=M;i++)
    {
        int x;
        cin>>x;
        T.push_back(x);
    }
    T.push_back(W);
    sort(T.begin(),T.end());
    for(int i=1;i<T.size();i++)
    {
        rez+=fr[T[i]-T[i-1]];
    }
    T.clear();
    cout<<rez;
    return 0;
}
