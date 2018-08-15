#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

string S[300005];
int lowest[300005];
int lvl[300005];
int N;
map<int,int> how_Many_First;
map<int,int> how_Many_Second;

int main(){

    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> S[i];
        for(auto it:S[i]){
            lvl[i] += (it == '(' ? 1:-1);
            lowest[i] = min(lowest[i],lvl[i]);
        }
    }

    long long ans = 0;

    for(int i = 1;i <= N;i++){

        if(lowest[i] >= 0){
            ans += how_Many_Second[-lvl[i]];
        }
        if(lowest[i] == lvl[i]){
            ans += how_Many_First[-lvl[i]];
        }
        if(lvl[i] == 0 && lowest[i] >= 0 && lowest[i] + lvl[i] >= 0){
            ans++;
        }

        if(lowest[i] == lvl[i]){
            how_Many_Second[lvl[i]]++;
        }
        if(lowest[i] >= 0){
            how_Many_First[lvl[i]]++;
        }

    }

    cout << ans;

    return 0;
}
