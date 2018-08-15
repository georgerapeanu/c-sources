#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int N,D1,D2;
vector<int> G[600 * 600 + 5];
int viz[600 * 600 + 5];
int type[600 * 600 + 5];

int hsh(int x,int y){
    return x * 2 * N + y;
}

void build(int D){
    for(int i = 0;i < 600 * 600 + 5;i++){
        G[i].clear();
        viz[i] = 0;
    }

    for(int s = 0;s <= 2 * N;s++){
        if(D < 1LL * s * s){
            continue;
        }
        int t = sqrt(D - 1LL * s * s);
        if(1LL * t * t + 1LL * s * s != D){
            continue;
        }
        for(int x = 0;x < 2 * N - s;x++){
            for(int y = 0;y < 2 * N - t;y++){
                G[hsh(x,y)].push_back(hsh(x + s,y + t));
                G[hsh(x + s,y + t)].push_back(hsh(x,y));
            }
            for(int y = 2 * N - 1;y >= t;y--){
                G[hsh(x,y)].push_back(hsh(x + s,y - t));
                G[hsh(x + s,y - t)].push_back(hsh(x,y));
            }
        }
        for(int x = 2 * N - 1;x >= s;x--){
            for(int y = 0;y < 2 * N - t;y++){
                G[hsh(x,y)].push_back(hsh(x - s,y + t));
                G[hsh(x - s,y + t)].push_back(hsh(x,y));
            }
            for(int y = 2 * N - 1;y >= t;y--){
                G[hsh(x,y)].push_back(hsh(x - s,y - t));
                G[hsh(x - s,y - t)].push_back(hsh(x,y));
            }
        }
    }
}

void mark(int shift){
    for(int x = 0;x < 2 * N;x++){
        for(int y = 0;y < 2 * N;y++){
            if(!viz[hsh(x,y)]){
                queue<pair<pair<int,int>,int> > Q;
                Q.push({{x,y},1});
                viz[hsh(x,y)] = 1;
                type[hsh(x,y)] |= 1 << shift;
                while(!Q.empty()){
                    int x = Q.front().first.first;
                    int y = Q.front().first.second;
                    int part = Q.front().second;
                    Q.pop();
                    for(auto it:G[hsh(x,y)]){
                        if(!viz[it]){
                            viz[it] = 1;
                            type[it] |= (!part) << shift;
                            Q.push({{it / (2 * N),it % (2 * N)},!part});
                        }
                    }
                }
            }
        }
    }
}

vector<pair<int,int> > fr[4];

int main(){
    cin >> N >> D1 >> D2;

    build(D1);
    mark(0);
    build(D2);
    mark(1);

    for(int x = 0;x < 2 * N;x++){
        for(int y = 0;y < 2 * N;y++){
            fr[type[hsh(x,y)]].push_back({x,y});
        }
    }

    for(int k = 0;k < 4;k++){
        if(fr[k].size() >= N * N){
            int num = N * N;
            for(auto it:fr[k]){
                cout << it.first << " " << it.second << "\n";
                num--;
                if(!num){
                    return 0;
                }
            }
        }
    }

    return 0;
}
