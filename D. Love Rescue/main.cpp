#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
string a,b;
vector<pair<char,char> > V;
int DSU[35];
int findroot(int nod){if(!DSU[nod]){return nod;}return DSU[nod] = findroot(DSU[nod]);}
bool uniot(int x,int y){
x = findroot(x);y = findroot(y);if(x == y){return 0;}DSU[x] = y;return 1;
}
int main()
{
    cin >> N >> a >> b;
    for(int i = 0;i < (int)a.size();i++){
        if(uniot(a[i] - 'a' + 1,b[i] - 'a' + 1)){
            V.push_back({a[i],b[i]});
        }
    }
    cout << V.size() << "\n";
    for(auto it:V){
        cout << it.first << " " << it.second << "\n";
    }
    return 0;
}
