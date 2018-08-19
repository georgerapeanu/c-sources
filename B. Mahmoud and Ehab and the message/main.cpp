#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
int N,M,K;
string V[100005];
int C[100005];
map<string,int> gr;
int minC[100005];
int main(){
    cin >> N >> K >> M;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
    }
    for(int i = 1;i <= N;i++){
        cin >> C[i];
    }
    for(int i = 1;i <= K;i++){
        minC[i] = 1 << 30;
        int x;
        cin >> x;
        while(x--){
            int p;
            cin >> p;
            gr[V[p]] = i;
            minC[i] = min(minC[i],C[p]);
        }
    }
    long long rez = 0;
    for(int i = 1;i <= M;i++){
        string a;
        cin >> a;
        rez += minC[gr[a]];
    }
    cout << rez;
    return 0;
}
