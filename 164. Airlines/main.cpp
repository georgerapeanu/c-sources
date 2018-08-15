#include <iostream>
#include <algorithm>
using namespace std;
int colors[205][205];
int dist[205][205];
int N,M;
int main(){
    cin >> N >> M;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            cin >> colors[i][j];
            dist[i][j] = (colors[i][j] <= M / 2 ? 1 : 1 << 28);
        }
    }
    for(int k = 1;k <= N;k++){
        for(int i = 1;i <= N;i++){
            if(i != k){
                for(int j = 1;j <= N;j++){
                    if(i != j && j != k){
                        dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
    bool ok = 1;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            ok &= (dist[i][j] < 4);
        }
    }
    if(ok){
        cout << M / 2 << "\n";
        for(int i = 1;i <= M / 2;i++){
            cout << i << " ";
        }
    }
    else{
        cout << M - M / 2 << "\n";
        for(int i = M / 2 + 1;i <= M;i++){
            cout << i << " ";
        }
    }
    return 0;
}
