#include <fstream>
#include <algorithm>
#include <deque>
using namespace std;
ifstream f("raci.in");
ofstream g("raci.out");
string a;
deque<int> D[30];
int dp[500005];
int N,K,rez;
int main(){
    f >> N >> K;
    for(int i = 1;i <= N;i++){
        f >> a;
        while(!D[a[0] - 'a'].empty() && i - D[a[0] - 'a'].front() > K){
            D[a[0] - 'a'].pop_front();
        }
        if(!D[a[0] - 'a'].empty()){
            dp[i] = 1 + dp[D[a[0] - 'a'].front()];
        }
        else{
            dp[i] = 1;
        }
        while(!D[a.back() - 'a'].empty()&& dp[D[a.back() - 'a'].back()] <= dp[i]){
            D[a.back() - 'a'].pop_back();
        }
        D[a.back() - 'a'].push_back(i);
        rez = max(rez,dp[i]);
    }
    g << rez;
    f.close();
    g.close();
    return 0;
}
