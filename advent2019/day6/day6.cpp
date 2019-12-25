#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


string s,a,b;
map<string,vector<string> > graph;
map<string,string> father;
map<string,int> dist1;
map<string,int> dist2;

void dfs(const string &root,const int &lvl,long long &ans) {
    ans += lvl;

    for(auto it:graph[root]) {
        father[it] = root;
        dfs(it,lvl + 1,ans);
    }
}

int main() {

    while(cin >> s) {
        bool found = 0;
        a = "";
        b = "";
        for(int i = 0; i < (int)s.size(); i++) {
            if(s[i] == ')') {
                found = true;
            }
            else if(found == false) {
                a += s[i];
            }
            else {
                b += s[i];
            }
        }
        graph[a].push_back(b);
    }

    long long ans = 0;

    dfs("COM",0,ans);

    ///cout << ans;

    string u = father["YOU"];
    string v = father["SAN"];

    int dist_u = 0;

    while(true) {
        dist1[u] = dist_u++;
        if(u == "COM") {
            break;
        }
        u = father[u];
    }

    int dist_v = 0;

    while(true) {
        dist2[v] = dist_v++;
        if(v == "COM") {
            break;
        }
        v = father[v];
    }

    ans = 1LL << 60;

    for(auto it:dist1) {
        if(dist2.count(it.first)) {
            ans = min(ans,(long long)it.second + dist2[it.first]);
        }
    }

    cout << ans;

    return 0;
}
