#include <bits/stdc++.h>

using namespace std;

int n;
string s;

vector<pair<int,int> > v;
long long ans = 0;

void pop_stack(){
    if(v.size() == 2){
        ans -= 1LL * v[1].first * (v[1].first + 1) / 2;
    }

    int delta = (v[(int)v.size() - 1].second - v[(int)v.size() - 1].first) - max(0,v[(int)v.size() - 2].second - v[(int)v.size() - 1].first);
    ans -= 1LL * delta * v[(int)v.size() - 1].first;

    v.pop_back();
}

void push_stack(pair<int,int> p){
    v.push_back(p);
    if(v.size() == 2){
        ans += 1LL * v[1].first * (v[1].first + 1) / 2;
    }
    int delta = (v[(int)v.size() - 1].second - v[(int)v.size() - 1].first) - max(0,v[(int)v.size() - 2].second - v[(int)v.size() - 1].first);
    ans += 1LL * delta * v[(int)v.size() - 1].first;
}

int main(){

    cin >> n;
    cin >> s;

    s = " " + s;

    int len = 0;

    v = {{0,0}};

    long long real_ans = 0;

    for(int i = 1;i <= n;i++){
        if(s[i] == '0'){
            len = 0;
        }
        else{
            len++;
        }
        while((int)v.size() > 1 && v.back().first <= len){
            pop_stack();
        }
        push_stack({len,i});
        real_ans += ans;
    //    cout << ans << endl;
    }

    cout << real_ans << "\n";

    return 0;
}
