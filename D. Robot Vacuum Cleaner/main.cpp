#include <iostream>
#include <algorithm>

using namespace std;
string S[100005];
long long inner[100005];
pair<int,int> V[100005];
int N;
long long rez = 0;
bool cmp(pair<int,int> a,pair<int,int>b){
    return 1LL * a.second * b.first < 1LL * a.first * b.second;
}
int main()
{
    cin >> N;
    int SS = 0,TT = 0;
    for(int i = 1;i <= N;i++){
        cin >> S[i];
        int s = 0,t = 0;
        for(auto it:S[i]){
            if(it == 's'){
                s++;
            }
            else{
                t++;
                inner[i] += s;
            }
        }
        V[i] = {s,t};
        rez += inner[i];
        SS += s;
        TT += t;
    }
    sort(V + 1,V + 1 + N,cmp);
    SS = TT = 0;
    for(int i = 1;i <= N;i++){
        rez += 1LL * V[i].second * SS;
        SS += V[i].first;
        TT += V[i].second;
    }
    cout << rez;
    return 0;
}
