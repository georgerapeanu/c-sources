#include <bits/stdc++.h>

using namespace std;

int n;
string s;

vector<int> pos1[30];
vector<int> pos2[30];

int perm[200005];

int aib[200005];

void update(int pos,int val){
    for(;pos;pos -= (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;

    for(;pos <= n;pos += (-pos) & pos){
        ans += aib[pos];
    }

    return ans;
}

int main() {
    cin >> n;
    cin >> s;

    vector<int> to(n,0);

    for(int i = 0;i < n;i++){
        pos1[s[i] - 'a'].push_back(i);
    }
    
    reverse(s.begin(),s.end());

    for(int i = 0;i < n;i++){
        pos2[s[i] - 'a'].push_back(i);
    }

    long long ans = 0;

    for(int i = 0;i < 30;i++){
        for(int j = 0;j < (int)pos1[i].size();j++){
            perm[pos2[i][j]] = pos1[i][j];
        }
    }

   
    for(int i = 0;i < n;i++){
        ans += query(perm[i] + 1);
        update(perm[i] + 1,1);
    }

    printf("%lld\n",ans);


    return 0;
}
