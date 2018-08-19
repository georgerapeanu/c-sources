#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
int N,M;
int T[100005];
int A[100005];
long long rez;
multiset<int> G[100005];
int fi(int nod){
    if(T[nod] <= 0){
        return nod;
    }
    return T[nod] = fi(T[nod]);
}
void u(int x,int y,bool baga){
    x = fi(x);
    y = fi(y);
    if(baga){
        rez += *G[x].begin();G[x].erase(G[x].begin());
        rez += *G[y].begin();G[y].erase(G[y].begin());
        T[x]++;
        T[y]++;
    }
    if(T[x] < T[y]){
        for(auto it:G[y]){
            G[x].insert(it);
        }
        T[x] += T[y];
        T[y] = x;
    }
    else{
        for(auto it:G[x]){
            G[y].insert(it);
        }
        T[y] += T[x];
        T[x] = y;
    }
}
class cmp{
    public:
    bool operator() (int a,int b){
        return T[a] > T[b];
    }
};
priority_queue<int,vector<int>,cmp> H;
int main(){
    cin >> N >> M;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
        T[i] = -1;
        G[i].insert(A[i]);
    }
    for(int i = 1;i <= M;i++){
        int x,y;
        cin >> x >> y;
        x++;
        y++;
        u(x,y,0);
    }
    for(int i = 1;i <= N;i++){
        if(T[i] <= 0){
            H.push(i);
        }
    }
    rez = 0;
    while(M < N - 1){
        if(H.size() < 2){
            cout << "Impossible";
            return 0;
        }
        int a = H.top();H.pop();
        int b = H.top();H.pop();
        if(T[b] == 0){
            cout << "Impossible";
            return 0;
        }
        u(a,b,1);
        H.push(fi(a));
        M++;
    }
    cout << rez;
    return 0;
}
