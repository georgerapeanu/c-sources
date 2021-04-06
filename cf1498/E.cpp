#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500;

int n;
int k[NMAX + 5];

vector<pair<int,pair<int,int> > > stuff;

bool ask(const pair<int,int> &a){
    string ans;
    cout << "? " << a.first << " " << a.second << endl;
    cin >> ans;
    return ans == "Yes";
}

void answer(const pair<int,int> &a){
    cout << "! " << a.first << " " << a.second << endl;
    exit(0);
}

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> k[i];
    }
    
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i != j && k[i] <= k[j]){
                stuff.push_back({k[i] - k[j],{j,i}});
            }
        }
    }

    sort(stuff.begin(),stuff.end());

    for(auto it:stuff){
        if(ask(it.second)){
            answer(it.second);
        }
    }

    answer({0,0});

    return 0;
}
