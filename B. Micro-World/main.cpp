#include <iostream>
#include <algorithm>

using namespace std;

int N,K;
pair<int,int> V[200005];

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> N >> K;
    for(int i = 1;i <= N;i++){
        cin >> V[i].first;
        V[i].second = 1;
    }

    sort(V + 1,V + 1 + N);

    int len = 1;
    for(int i = 2;i <= N;i++){
        if(V[len].first == V[i].first){
            V[len].second += V[i].second;
        }
        else{
            V[++len] = V[i];
        }
    }

    int ans = N;
    N = len;

    for(int i = 2;i <= N;i++){
        if(V[i - 1].first + K >= V[i].first){
            ans -= V[i - 1].second;
        }
    }

    cout << ans;

    return 0;
}
