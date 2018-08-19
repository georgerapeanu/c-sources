#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;
int N,M,C;
int V[1005];
int nrpasi;
bool ok(){
    for(int i = 1;i <= N;i++)
    {
        if(!V[i] || V[i] > V[i+1]){
            return 0;
        }
    }
    return 1;
}
void pushL(int val){
    int ind = 1;
    while(V[ind] && !(V[ind - 1] <= val && val < V[ind])){
        ind++;
    }
    V[ind] = val;
    cout << ind << endl;
}
void pushR(int val){
    int ind = N;
    while(V[ind] && !(V[ind] < val && val <= V[ind + 1])){
        ind--;
    }
    V[ind] = val;
    cout << ind << endl;
}
int main(){
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    cin >> N >> M >> C;
    V[N + 1] = 100000;
    while(!ok())
    {
        nrpasi++;
        if(nrpasi > M)
            while(1);
        int val = 0;
        cin >> val;
        if(val <= C/2){
            pushL(val);
        }
        else{
            pushR(val);
        }
    }
    return 0;
}
