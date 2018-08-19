#include <iostream>
#include <queue>
using namespace std;
int nrWatered = 0;
bool viz[205];
int maxi = 0;
queue<pair<int,int> > Q;
int N,T,K;
int main()
{
    cin >> T;
    while(T--){
        for(int i = 1;i <= N;i++){
            viz[i] = 0;
        }
        while(!Q.empty()){
            Q.pop();
        }
        cin >> N >> K;
        for(int i = 1;i <= K;i++){
            int x;
            cin >> x;
            Q.push({x,1});
            viz[x] = 1;
        }
        nrWatered = 0;
        maxi = 1;
        while(!Q.empty()){
            viz[Q.front().first] = 1;
            pair<int,int> tmp = Q.front();Q.pop();
            maxi = max(maxi,tmp.second);
            nrWatered++;
            viz[tmp.first] = 1;
            if(nrWatered == N){
                break;
            }
            if(tmp.first > 1 && !viz[tmp.first - 1]){
                viz[tmp.first - 1] = 1;
                Q.push({tmp.first - 1,tmp.second + 1});
            }
            if(tmp.first < N && !viz[tmp.first + 1]){
                viz[tmp.first + 1] = 1;
                Q.push({tmp.first + 1,tmp.second + 1});
            }
        }
        cout << maxi << "\n";
    }
    return 0;
}
