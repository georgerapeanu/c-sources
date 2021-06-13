#include <bits/stdc++.h>

using namespace std;

int tests;
string s,e;
deque<int> a,b;

deque<int> transform(string s) {
    deque<int> ans;
    int len = 0;
    int last = -1;
    for(auto it:s) {
        if(last != it) {
            if(len > 0) {
                ans.push_back(len);
            }
            len = 0;
            last = it;
        }
        len++;
    }
    if(len > 0) {
        ans.push_back(len);
    }
    return ans;
}

string mult(string s){
    return s + "0";
}

string _not(string s){
    for(auto &it:s){
        it = 1 - (it - '0') + '0';
    }
    int k = 0;
    while(k < (int)s.size() && s[k] == '0'){
        k++;
    }
    
    string ans = "";

    for(int i = k;i < (int)s.size();i++){
        ans += s[i];
    }
    if(ans == ""){
        ans = "0";
    }
    return ans;
}

int solve(string s,string e) {
    map<string,int> dist;
    dist[s] = 1;
    queue<string> q;
    q.push(s);

    while(q.empty() == false){
        string nod = q.front();
        q.pop();
        if(nod == e){
            return dist[nod] - 1;
        }
        if(dist[nod] > 20){
            continue;
        }
        if(dist[_not(nod)] == 0){
            dist[_not(nod)] = dist[nod] + 1;
            q.push(_not(nod));
        }
        if(dist[mult(nod)] == 0){
            dist[mult(nod)] = dist[nod] + 1;
            q.push(mult(nod));
        }
    }

    return -1;
}

int main() {

    cin >> tests;

    for(int test = 1; test <= tests; test++) {
        cout << "Case #" << test << ": ";
        cin >> s >> e;
        if(s == e) {
            cout << 0;
        } else if(s == "0") {
            s = "1";
            int ans = solve(s,e);
            if(ans == -1) {
                cout << "IMPOSSIBLE";
            } else {
                cout << ans + 1;
            }
        } else if(e == "0") {
            cout << transform(s).size();
        } else {
            int ans = solve(s,e);
            if(ans == -1) {
                cout << "IMPOSSIBLE";
            } else {
                cout << ans;
            }
        }
        cout << "\n";
    }

    return 0;
}
