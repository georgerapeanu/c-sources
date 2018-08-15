#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long eval(vector<pair<int,int> > &V){
    long long ans = 0;
    int poz = 0;
    for(auto it:V){
        if(it.first <= poz && it.second >= poz){
            continue;
        }
        if(it.first > poz){
            ans += it.first - poz;
            poz = it.first;
        }
        else{
            ans += poz - it.second;
            poz = it.second;
        }
    }
    ans += (poz < 0 ? -poz:poz);
    return ans;
}

int N;
pair<int,int> V[100005];

class Cmp1{
    public:
    bool operator () (int a,int b){
        return V[a].second > V[b].second;
    }
};

class Cmp2{
    public:
    bool operator () (int a,int b){
        return V[a].first < V[b].first;
    }
};

priority_queue<int,vector<int>,Cmp1> minRight;
priority_queue<int,vector<int>,Cmp2> maxLeft;

bool U[100005];

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i].first >> V[i].second;
    }


    vector<pair<int,int> > ord;

    for(int i = 1;i <= N;i++){
        minRight.push(i);
        maxLeft.push(i);
        U[i] = 0;
    }

    for(int i = 1;i <= N;i++){
        if(i & 1){
            while(U[minRight.top()]){
                minRight.pop();
            }
            ord.push_back(V[minRight.top()]);
            U[minRight.top()] = 1;
        }
        else{
            while(U[maxLeft.top()]){
                maxLeft.pop();
            }
            ord.push_back(V[maxLeft.top()]);
            U[maxLeft.top()] = 1;
        }
    }

    long long rez = eval(ord);

    ord.clear();

    for(int i = 1;i <= N;i++){
        minRight.push(i);
        maxLeft.push(i);
        U[i] = 0;
    }

    for(int i = 1;i <= N;i++){
        if(!(i & 1)){
            while(U[minRight.top()]){
                minRight.pop();
            }
            ord.push_back(V[minRight.top()]);
            U[minRight.top()] = 1;
        }
        else{
            while(U[maxLeft.top()]){
                maxLeft.pop();
            }
            ord.push_back(V[maxLeft.top()]);
            U[maxLeft.top()] = 1;
        }
    }

    rez = max(rez,eval(ord));

    cout << rez;

    return 0;
}
